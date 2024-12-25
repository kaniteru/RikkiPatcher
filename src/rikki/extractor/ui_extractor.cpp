#include "ui_extractor.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/ui/ui_json.hpp"
#include "rikki/data/ui/key/ui_key.hpp"
#include "rikki/data/ui/key/ui_text_dialog_key.hpp"
#include "rikki/data/ui/key/ui_text_setting_key.hpp"
#include "rikki/data/ui/key/ui_text_in_game_key.hpp"
#include "rikki/stream/ui_patch_stream.hpp"

#include "utils/string_util.hpp"
#include "utils/ui_text_util.hpp"
#include "utils/filesystem_util.hpp"
#include "utils/instance_factory.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    UITextExtractor
// ======================== C L A S S ========================

size_t UITextExtractor::extract() {
    path_t file { };

    if (!UITextUtil::copy_startup_from_game_and_decrypt(file)) {
        return 0;
    }

    UIText ut(file);

    UITextUtil::encrypt_startup_and_move_to_game();

    if (!ut.is_valid()) {
        return 0;
    }

    InGameUITextExtractor inGame(ut, m_db);
    SettingUITextExtractor setting(ut, m_db);
    DialogUITextExtractor dialog(ut, m_db);

    size_t result = 0;
    result += IExtractor::do_extract(&inGame);
    result += IExtractor::do_extract(&setting);
    result += IExtractor::do_extract(&dialog);
    return result;
}

UITextExtractor::UITextExtractor(const path_t& dst) :
    m_db(dst) { }

// ======================== C L A S S ========================
// ===    IUITextExtractor
// ======================== C L A S S ========================

IUITextExtractor::IUITextExtractor(UIText& ut) :
    m_ut(ut) { }

// ======================== C L A S S ========================
// ===    InGameUITextExtractor
// ======================== C L A S S ========================

size_t InGameUITextExtractor::extract() {
    size_t total = 0;
    size_t failed = 0;
    size_t ok = 0;

    InGameUIText ig { };

    for (const auto& [pKey, val] : ig.m_map) {
        const auto key = InGameUITextKeyMgr::g_keys.at(pKey);

        std::string buf { };
        m_ut.get_in_game(key, buf);
        val = buf;
    }

    UITextPatchStream patchStream(m_db);
    patchStream.set_texts<InGameUIText>(ig);

    if (!patchStream.save()) {
        return 0;
    }

    return ok;
}

InGameUITextExtractor::InGameUITextExtractor(UIText& ut, const path_t& dst) :
    IExtractor(),
    IUITextExtractor(ut) {

    std::filesystem::create_directories(path_t(dst).append(FOLDER_BASE));
    m_db = path_t(dst).append(FOLDER_BASE).append(FILE_NAME);
}

// ======================== C L A S S ========================
// ===    SettingUITextExtractor
// ======================== C L A S S ========================

size_t SettingUITextExtractor::extract() {
    size_t total = 0;
    size_t failed = 0;
    size_t ok = 0;

    SettingUIText s { };

    for (const auto& [pKey, val] : s.m_map) {
        const auto& key = SettingUITextKeyMgr::g_keys.at(pKey);

        SettingUITextEntry buf { };
        m_ut.get_setting(key, buf);
        val = buf;
    }

    for (const auto& [pKey, val] : s.m_ControlsUsageMap) {
        const auto& key = SettingUITextKeyMgr::g_keys.at(pKey);

        SettingUITextEntry buf { };
        m_ut.get_setting(key, buf);
        val = buf;
    }

    UITextPatchStream patchStream(m_db);
    patchStream.set_texts<SettingUIText>(s);

    if (!patchStream.save()) {
        return 0;
    }

    return ok;
}

SettingUITextExtractor::SettingUITextExtractor(UIText& ut, const path_t& dst) :
    IExtractor(),
    IUITextExtractor(ut) {

    std::filesystem::create_directories(path_t(dst).append(FOLDER_BASE));
    m_db = path_t(dst).append(FOLDER_BASE).append(FILE_NAME);
}

// ======================== C L A S S ========================
// ===    DialogUITextExtractor
// ======================== C L A S S ========================

size_t DialogUITextExtractor::extract() {
    size_t total = 0;
    size_t failed = 0;
    size_t ok = 0;

    DialogUIText d { };

    for (const auto& [pKey, val] : d.m_type1Map) {
        const auto& key = DialogUITextKeyMgr::g_type1Keys.at(pKey);

        DialogUITextEntry buf { };
        m_ut.get_dialog_type1(key, buf);
        val = buf;
    }

    for (const auto& [pKey, val] : d.m_type2Map) {
        const auto& key = DialogUITextKeyMgr::g_type2Keys.at(pKey);

        DialogUITextEntry buf { };
        m_ut.get_dialog_type2(key, buf);
        val = buf;
    }

    UITextPatchStream patchStream(m_db);
    patchStream.set_texts<DialogUIText>(d);

    if (!patchStream.save()) {
        return 0;
    }

    return ok;
}

DialogUITextExtractor::DialogUITextExtractor(UIText& ut, const path_t& dst) :
    IExtractor(),
    IUITextExtractor(ut) {

    std::filesystem::create_directories(path_t(dst).append(FOLDER_BASE));
    m_db = path_t(dst).append(FOLDER_BASE).append(FILE_NAME);
}
