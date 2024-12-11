#include "dialogue_migr_stream.hpp"
#include "rikki/dir_mgr.hpp"

#include "utils/json_util.hpp"
#include "utils/hash_util.hpp"
#include "utils/filesystem_util.hpp"
#include "utils/instance_factory.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    DialogueMigrStream
// ======================== C L A S S ========================

std::string DialogueMigrStream::get_file_hash() const {
    if (!m_j.contains(KEY_HASH)) {
        return { };
    }

    return m_j[KEY_HASH];
}

dialogue_map_t DialogueMigrStream::get_dialogues() const {
    dialogue_map_t result { };

    if (!m_j.contains(KEY_LIST)) {
        return result;
    }

    for (auto& entries = m_j[KEY_LIST]; auto& it : entries.items()) {
        dialogue_idx_t idx = std::stoi(it.key());
        const auto& e = it.value();

        const std::string spk = e[KEY_SPEAKER];
        std::vector<DialogueSpan> dialogues { };

        for (const auto& diaJ = e[KEY_DIALOGUE]; const auto& dia : diaJ) {
            DialogueSpan span { };
            span.m_html = dia[KEY_DIA_HTML];
            span.m_text = dia[KEY_DIA_TEXT];

            dialogues.emplace_back(std::move(span));
        }

        result[idx] = { spk, dialogues };
    }

    return result;
}

bool DialogueMigrStream::get_dialogue(const dialogue_idx_t idx, DialogueEntry& e) const {
    auto& j = m_j[KEY_LIST][std::to_string(idx)];

    if (j.is_null()) {
        return false;
    }

    e.m_speaker = j[KEY_SPEAKER];

    for (const auto& dia : j[KEY_DIALOGUE]) {
        DialogueSpan span { };
        span.m_html = dia[KEY_DIA_HTML];
        span.m_text = dia[KEY_DIA_TEXT];

        e.m_dialogues.emplace_back(std::move(span));
    }

    return true;
}

void DialogueMigrStream::save_migration_data(const path_t& dir) {
    const auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);

    size_t total = 0;
    size_t failed = 0;
    size_t ok = 0;

    for (const auto files = FilesystemUtil::sort_files(gmdir); const auto& f : files) {
        const auto fName = f.filename().generic_u8string();
        auto log = fName + std::u8string(u8" => ");

        total++;

        Dialogue dia(f);

        if (!dia.is_valid()) {
            log += u8"Read failed";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        const auto hash = HashUtil::file_to_hash(f);

        nlohmann::ordered_json j { };
        j[KEY_HASH] = hash;

        auto& list = j[KEY_LIST];

        for (const auto& [k, v] : dia.extract_dialogues()) {
            const auto& idx = k;
            const auto& [spk, dia] = v;

            auto& entry = list[std::to_string(idx)];
            entry[KEY_SPEAKER] = spk;

            for (const auto& [html, text] : dia) {
                entry[KEY_DIALOGUE] += { { KEY_DIA_HTML, html }, { KEY_DIA_TEXT, text } };
            }
        }

        if (JsonUtil::save_into_file(j, path_t(dir).append(fName))) {
            log += u8"OK";
            ok++;
        }
        else {
            log += u8"Write failed";
            failed++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    const auto log = "Total: " + std::to_string(total) + " | migrated: " + std::to_string(ok) + " | Failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
}

DialogueMigrStream::DialogueMigrStream(const path_t& file) :
    IMigrStream() {

    m_isValid = JsonUtil::load_from_file(m_j, file);
}

// ======================== C L A S S ========================
// ===    ChoiceMigrStream
// ======================== C L A S S ========================

std::string ChoiceMigrStream::get_file_hash() const {
    if (!m_j.contains(KEY_HASH)) {
        return { };
    }

    return m_j[KEY_HASH];
}

choice_map_t ChoiceMigrStream::get_choices() const {
    choice_map_t result { };

    if (!m_j.contains(KEY_LIST)) {
        return result;
    }

    for (const auto& list = m_j[KEY_LIST]; const auto& it : list.items()) {
        const choice_idx_t idx = std::stoi(it.key());
        result[idx] = it.value();
    }

    return result;
}

void ChoiceMigrStream::save_migration_data(const path_t& dir) {
    const auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);

    size_t total = 0;
    size_t failed = 0;
    size_t ok = 0;

    for (const auto files = FilesystemUtil::sort_files(gmdir); const auto& f : files) {
        const auto fName = f.filename().generic_u8string();
        auto log = fName + std::u8string(u8" => ");

        total++;

        Dialogue dia(f);

        if (!dia.is_valid()) {
            log += u8"Read failed";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        const auto hash = HashUtil::file_to_hash(f);

        nlohmann::ordered_json j { };
        j[KEY_HASH] = hash;

        auto& list = j[KEY_LIST];

        for (const auto& [idx, cho] : dia.extract_choices()) {
            list[std::to_string(idx)] = cho;
        }

        if (JsonUtil::save_into_file(j, path_t(dir).append(fName))) {
            log += u8"OK";
            ok++;
        }
        else {
            log += u8"Write failed";
            failed++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    const auto log = "Total: " + std::to_string(total) + " | migrated: " + std::to_string(ok) + " | Failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
}

ChoiceMigrStream::ChoiceMigrStream(const path_t& file) :
    IMigrStream() {

    m_isValid = JsonUtil::load_from_file(m_j, file);
}
