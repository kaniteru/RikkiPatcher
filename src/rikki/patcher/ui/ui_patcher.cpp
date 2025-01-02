#include "ui_patcher.hpp"
#include "rikki/data/data_path.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/ui_text/ui_text.hpp"
#include "rikki/data/ui_dialogue/ui_dialogue.hpp"
#include "rikki/data/ui_dialogue/ui_dialogue_key.hpp"
#include "ui_text_patcher.hpp"
#include "ui_dialogue_patcher.hpp"
#include "rikki/extractor/ui/ui_extractor.hpp"

#include "utils/ui_text_util.hpp"
#include "utils/filesystem_util.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    UIPatcher
// ======================== C L A S S ========================

PatcherResult UIPatcher::patch() { // todo: check file exists
    if (!m_isAvailable) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't copied the game file from game directory");
        return { };
    }

    if (!m_pUI->is_valid()) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't read the game data");
        return { };
    }

    PatcherResult result { };

    {
        UIText ut(m_pUI.get());

        // apply ui-texts
        WvInvoker::log(LOG_LV_ALERT, "Start apply custom ui-texts data into game");
        UITextPatcher textPatcher(m_dir, &ut);
        result += textPatcher.patch();
        WvInvoker::log(LOG_LV_ALERT, "Finished apply custom ui-texts data into game");
    }

    {
        WvInvoker::log(LOG_LV_ALERT, "Start apply custom ui-dialogues data into game");
        UIDialoguePatcher diaPatcher(m_dir, m_pUI.get());
        result += diaPatcher.patch();
        WvInvoker::log(LOG_LV_ALERT, "Finished apply custom ui-dialogues data into game");

        WvInvoker::log(LOG_LV_ALERT, "Start apply custom ui-choices data into game");
        UIChoicePatcher choPatcher(m_dir, m_pUI.get());
        result += choPatcher.patch();
        WvInvoker::log(LOG_LV_ALERT, "Finished apply custom ui-choices data into game");
    }

    return result;
}

PatcherResult UIPatcher::migration() {
    if (!m_isAvailable) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't copied the game file from game directory");
        return { };
    }

    if (!m_pUI->is_valid()) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't read the game data");
        return { };
    }

    PatcherResult result { };

    {
        UIText ut(m_pUI.get());

        // apply ui-texts
        WvInvoker::log(LOG_LV_ALERT, "Start the migration of ui-texts data");
        UITextPatcher textPatcher(m_dir, &ut);
        result += textPatcher.migration();
        WvInvoker::log(LOG_LV_ALERT, "Finished the migration of ui-texts data");
    }

    {
        WvInvoker::log(LOG_LV_ALERT, "Start the migration of ui-dialogues data");
        UIDialoguePatcher diaPatcher(m_dir, m_pUI.get());
        result += diaPatcher.migration();
        WvInvoker::log(LOG_LV_ALERT, "Finished the migration of ui-dialogues data");

        WvInvoker::log(LOG_LV_ALERT, "Start the migration of ui-choices data");
        UIChoicePatcher choPatcher(m_dir, m_pUI.get());
        result += choPatcher.migration();
        WvInvoker::log(LOG_LV_ALERT, "Finished the migration of ui-choices data");
    }

    return result;
}

PatcherResult UIPatcher::generate_migration_info() {
    if (m_isAvailable) {
        this->close();
    }
    else {
        WvInvoker::log(LOG_LV_ERR, u8"Can't copied the game file from game directory");
    }

    UIExtractor extractor(path_t(m_dir) / UITextPath::MIGR_BASE);
    extractor.extract();
    return { };
}

bool UIPatcher::close() {
    if (m_isAvailable && m_pUI) {
        if (!m_pUI->save()) {
            WvInvoker::log(LOG_LV_ERR, u8"Can't save the patched game file");
        }

        const auto s = UITextUtil::encrypt_startup_and_move_to_game();

        if (!s) {
            WvInvoker::log(LOG_LV_ERR, u8"Can't copied the patched game file to game directory");
        }

        m_pUI.reset();
        return s;
    }

    return false;
}

UIPatcher::UIPatcher(const path_t& src) :
    IPatcher(src) {

    if (path_t file { }; UITextUtil::copy_startup_from_game_and_decrypt(file)) {
        m_isAvailable = true;
        m_pUI = std::make_unique<UI>(file);
    }
}

UIPatcher::~UIPatcher() {
    this->close();
}
