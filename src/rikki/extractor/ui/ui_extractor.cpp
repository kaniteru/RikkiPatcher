#include "ui_extractor.hpp"
#include "rikki/data/data_path.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/ui_text/ui_text.hpp"
#include "ui_text_extractor.hpp"
#include "ui_dialogue_extractor.hpp"

#include "utils/ui_text_util.hpp"
#include "utils/filesystem_util.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    UIExtractor
// ======================== C L A S S ========================

size_t UIExtractor::extract() {
    path_t file { };

    if (!UITextUtil::copy_startup_from_game_and_decrypt(file)) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't copied the game file from game directory");
        return 0;
    }

    UI ui(file);

    UITextUtil::encrypt_startup_and_move_to_game();

    if (!ui.is_valid()) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't read the game data");
        return 0;
    }

    FilesystemUtil::delete_and_create_directories(path_t(m_dir) / UIPath::PATCH_BASE);

    size_t result = 0;

    {
        UITextExtractor extractor(m_dir, &ui);
        result += extractor.extract();
    }

    {
        UIDialogueExtractor extractor(m_dir, &ui);
        result += extractor.extract();
    }

    return result;
}

UIExtractor::UIExtractor(const path_t& dst) :
    IExtractor(dst) { }
