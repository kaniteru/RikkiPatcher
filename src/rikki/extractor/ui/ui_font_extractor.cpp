#include "ui_font_extractor.hpp"
#include "rikki/data/data_path.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/ui_font/ui_font_json.hpp"
#include "rikki/stream/ui_font_patch_stream.hpp"

#include "utils/filesystem_util.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

size_t UIFontExtractor::extract() {
    FilesystemUtil::delete_and_create_directories(path_t(m_dir) / UIFontPath::PATCH_BASE);

    const auto fInfo = path_t(m_dir) / UIFontPath::PATCH_FILE_FONTS_INFO;
    const auto fFiles = path_t(m_dir) / UIFontPath::PATCH_FOLDER_FONTS_FILES;
    std::filesystem::create_directories(fFiles);

    UIFont uiFont(m_pUI);
    const auto pureFonts = uiFont.get_fonts();

    UIFontPatchStream stream(fInfo);
    const auto size = stream.add_fonts(pureFonts);

    if (!stream.save()) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't save the " + fInfo.filename().u8string());
        return { };
    }

    const auto log = "Extracted: " + std::to_string(size);
    WvInvoker::log(LOG_LV_INFO, log);
    return size;
}

UIFontExtractor::UIFontExtractor(const path_t& dst, UI* pUI) :
    IExtractor(dst),
    m_pUI(pUI) { }
