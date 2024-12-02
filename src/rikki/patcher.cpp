#include "patcher.hpp"
#include "utils/filesystem_util.hpp"
#include "wv/wv_invoker.hpp"
#include "wv/enums.hpp"
#include "data/dialogue.hpp"
#include "utils/json_util.hpp"
#include "dir_mgr.hpp"

void Extractor::extract_dialogues(const path_t& src, const path_t& dst) {
    nlohmann::json j { };
    std::stringstream ss { };
    size_t ssAdded = 0;

    auto u8 = u8"Start extract dialogues from " + src.generic_u8string();
    WvInvoker::log(LOG_LV_ALERT, reinterpret_cast<const char*>(u8.c_str()));

    auto files = FilesystemUtil::sort_files(src);
    WvInvoker::log(LOG_LV_INFO, std::string("Found " + std::to_string(files.size()) + " dialogue files"));

    for (const auto& it : files) {
        std::string log = it.filename().generic_string() + " => ";

        Dialogue dia(it);

        if (!dia.is_valid()) {
            WvInvoker::log(LOG_LV_PROG, log + "read failed");
            continue;
        }

        auto de = dia.extract();
        auto& spks = de.m_speakers;
        auto& dias = de.m_dialogues;

        log += "total [spk: " + std::to_string(spks.size()) + " | dia: " + std::to_string(dias.size()) + "]";
        WvInvoker::log(LOG_LV_PROG, log);

        for (const auto& s : spks) {
            j[s.first] = s.second;
        }

        for (const auto& d : dias) {
            ss << d << std::endl;
            ssAdded++;
        }
    }

    std::string result = "Extracted total [spk: " + std::to_string(j.size()) + " | dia: " + std::to_string(ssAdded) + "]";
    WvInvoker::log(LOG_LV_INFO, result);

    auto tranSpk = path_t(dst).append(FILE_SPEAKERS);
    auto tranDia = path_t(dst).append(FILE_DIALOGUES);

    std::string logSpk = "Save extracted speakers => ";
    std::string logDia  = "Save extracted dialogues => ";

    if (JsonUtil::save_into_file(j, tranSpk)) {
        logSpk += "OK";
    } else {
        logSpk += "FAILED";
    }

    WvInvoker::log(LOG_LV_INFO, logSpk);

    if (auto fs = std::fstream(tranDia, std::ios::out | std::ios::trunc); fs.is_open()) {
        fs << ss.str();
        fs.close();
        logDia += "OK";
    } else {
        logDia += "FAILED";
    }

    WvInvoker::log(LOG_LV_INFO, logDia);

    auto u8dst = u8"All extracted files saved in " + dst.generic_u8string();
    WvInvoker::log(LOG_LV_INFO, reinterpret_cast<const char*>(u8dst.c_str()));

    WvInvoker::log(LOG_LV_ALERT, "Finished extract dialogues");
}

void Patcher::load_and_patch(const path_t& src) {
    WvInvoker::log(LOG_LV_ALERT, "Patch started");

    if (!std::filesystem::exists(src)) {
        auto u8 = u8"Can't read " + src.generic_u8string();
        WvInvoker::log(LOG_LV_ERR, reinterpret_cast<const char*>(u8.c_str()));
        WvInvoker::log(LOG_LV_ALERT, "Patch finished");
        return;
    }

    auto pDirMgr = InstanceFactory::instance().get<DirMgr>();
    const auto spk = path_t(src).append(FILE_SPEAKERS);
    const auto dia = path_t(src).append(FILE_DIALOGUES);

    if (std::filesystem::exists(spk) || std::filesystem::exists(dia)) {
        WvInvoker::log(LOG_LV_DEBUG, "Found dialogue patch");
        const auto gmDia = pDirMgr->get(DIR_GAME_JSON_DIALOGUES);
        Patcher::update_dialogues(spk, dia, gmDia);
    }

    WvInvoker::log(LOG_LV_ALERT, "Patch finished");
}

void Patcher::update_dialogues(const path_t& spk, const path_t& dia, const path_t& dst) {
    _DialogueEntry de { };
    nlohmann::json j { };
    size_t diaAdded = 0;

    if (std::filesystem::exists(spk)) {
        WvInvoker::log(LOG_LV_ALERT, "Found " + std::string(FILE_SPEAKERS));

        if (JsonUtil::load_from_file(j, spk)) {
            for (auto& [k, v] : j.items()) {
                de.m_speakers[k] = v;
            }
        } else {
            WvInvoker::log(LOG_LV_ERR, "Can't read " + std::string(FILE_SPEAKERS));
        }
    }

    if (std::filesystem::exists(dia)) {
        WvInvoker::log(LOG_LV_ALERT, "Found " + std::string(FILE_DIALOGUES));

        if (auto fs = std::fstream(dia, std::ios::in); fs.is_open()) {
            std::string buf { };

            while (std::getline(fs, buf)) {
                de.m_dialogues.emplace_back(buf);
                diaAdded++;
            }

            fs.close();
        } else {
            WvInvoker::log(LOG_LV_ERR, "Can't read " + std::string(FILE_DIALOGUES));
        }
    }

    auto logLoaded = "Loaded total [spk: " + std::to_string(de.m_speakers.size()) + " | dia: " + std::to_string(diaAdded) + "]";
    WvInvoker::log(LOG_LV_INFO, logLoaded);

    auto u8 = u8"Start update dialogues from " + dst.generic_u8string();
    WvInvoker::log(LOG_LV_ALERT, reinterpret_cast<const char*>(u8.c_str()));

    auto files = FilesystemUtil::sort_files(dst);
    size_t found = files.size();
    WvInvoker::log(LOG_LV_INFO, std::string("Found " + std::to_string(found) + " dialogue files from game"));

    size_t updated = 0;

    for (const auto& it : files) {
        std::string log = it.filename().generic_string() + " => ";

        Dialogue dialogue(it);

        if (!dialogue.is_valid()) {
            WvInvoker::log(LOG_LV_PROG, log + "read failed");
            continue;
        }

        dialogue.update(de);

        if (dialogue.save()) {
            WvInvoker::log(LOG_LV_PROG, log + "updated");
            updated++;
        } else {
            WvInvoker::log(LOG_LV_PROG, log + "write failed");
        }
    }

    WvInvoker::log(LOG_LV_INFO, "Updated " + std::to_string(found) + " / " + std::to_string(updated) + " dialogue files");
    WvInvoker::log(LOG_LV_ALERT, "Finished update dialogues");
}

void Patcher::migration_modified_data(const path_t& src) {
    WvInvoker::log(LOG_LV_ALERT, u8"Starting the migration for " + src.generic_u8string());

}
