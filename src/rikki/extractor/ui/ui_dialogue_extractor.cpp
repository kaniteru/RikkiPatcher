#include "ui_dialogue_extractor.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/data_path.hpp"
#include "rikki/data/dialogue/i_dialogue.hpp"
#include "rikki/data/dialogue/dialogue_json.hpp"
#include "rikki/data/ui_dialogue/ui_dialogue.hpp"
#include "rikki/data/ui_dialogue/ui_dialogue_key.hpp"
#include "rikki/stream/dialogue_patch_stream.hpp"

#include "utils/string_util.hpp"
#include "utils/filesystem_util.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    UIDialogueExtractor
// ======================== C L A S S ========================

size_t UIDialogueExtractor::extract() {
    size_t result = 0;

    // dialogues
    WvInvoker::log(LOG_LV_ALERT, "Start extract ui-dialogues data from game");
    FilesystemUtil::delete_and_create_directories(m_dbDia);

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        auto log = StringUtil::cstr_to_u8(pFile) + std::u8string(u8" => ");

        UIDialogue dia(m_pUI, pKey);
        const auto map = dia.extract_dialogues();

        if (map.empty()) {
            log += u8"OK (no data)";
            WvInvoker::log(LOG_LV_PROG, log);
            continue;
        }

        const auto patched = std::to_string(map.size());
        log += std::u8string(patched.begin(), patched.end()) + u8" => ";

        const auto fPatch = path_t(m_dbDia).append(pFile);
        DialoguePatchStream patchStream(fPatch);
        patchStream.set_dialogues(map);

        if (!patchStream.save()) {
            log += u8"Failed";
        }
        else {
            log += u8"OK";
            result++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    WvInvoker::log(LOG_LV_ALERT, "Finished extract ui-dialogues data from game");

    // choices
    WvInvoker::log(LOG_LV_ALERT, "Start extract ui-choices data from game");
    FilesystemUtil::delete_and_create_directories(m_dbCho);

    for (const auto& [pKey, pFile] : UIDialogueKey::g_arr) {
        auto log = StringUtil::cstr_to_u8(pFile) + std::u8string(u8" => ");

        UIDialogue dia(m_pUI, pKey);
        const auto map = dia.extract_choices();

        if (map.empty()) {
            log += u8"OK (no data)";
            WvInvoker::log(LOG_LV_PROG, log);
            continue;
        }

        const auto patched = std::to_string(map.size());
        log += std::u8string(patched.begin(), patched.end()) + u8" => ";

        const auto fPatch = path_t(m_dbCho).append(pFile);
        ChoicePatchStream patchStream(fPatch);
        patchStream.set_choices(map);

        if (!patchStream.save()) {
            log += u8"Failed";
        }
        else {
            log += u8"OK";
            result++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    WvInvoker::log(LOG_LV_ALERT, "Finished extract ui-choices data from game");

    return result;
}

UIDialogueExtractor::UIDialogueExtractor(const path_t& dst, UI* pUI) :
    IExtractor(dst),
    m_dbDia(path_t(dst) / UIDialoguePath::PATCH_FOLDER_DIALOGUE),
    m_dbCho(path_t(dst) / UIDialoguePath::PATCH_FOLDER_CHOICE),
    m_pUI(pUI) { }
