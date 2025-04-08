#include "ui_font_patcher.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/dir_mgr_enum.hpp"
#include "rikki/data/data_path.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/ui_font/ui_font.hpp"
#include "rikki/data/ui_font/ui_font_json.hpp"
#include "rikki/stream/ui_font_patch_stream.hpp"

#include "utils/filesystem_util.hpp"

#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    UIFontPatcher
// ======================== C L A S S ========================

PatcherResult UIFontPatcher::patch() {
    const auto fInfo = path_t(m_dir) / UIFontPath::PATCH_FILE_FONTS_INFO;
    const auto fFiles = path_t(m_dir) / UIFontPath::PATCH_FOLDER_FONTS_FILES;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::PATCH_UI_DIALOGUE_START);

    UIFontPatchStream stream(fInfo);

    if (!stream.is_loaded()) {
        return { };
    }

    const auto fonts = stream.get_fonts();
    const auto lenFonts = static_cast<int32_t>(fonts.size());

    const UIFont uiFont(m_pUI);

    if (!uiFont.is_valid()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::PATCH_UI_FONT_FAILED_READ);
        return { 0, lenFonts, 0 };
    }

    uiFont.set_fonts(fonts);

    const auto fGm = DirMgr::get(DIR_GAME_FONTS);

    if (fs::exists(fFiles) && fs::is_directory(fFiles)) {
        fs::copy(fFiles, fGm, fs::copy_options::overwrite_existing);
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::PATCH_UI_FONT_RESULT, lenFonts, lenFonts, 0, 0);
    return { lenFonts, 0, 0 };
}

PatcherResult UIFontPatcher::migration() {
    /*const auto fInfo = path_t(m_dir) / UIFontPath::PATCH_FILE_FONTS_INFO;
    const auto fFiles = path_t(m_dir) / UIFontPath::PATCH_FOLDER_FONTS_FILES;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::MIGR_UI_DIALOGUE_START);

    fs::create_directories(fFiles);

    const UIFont uiFont(m_pUI);

    if (!uiFont.is_valid()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::MIGR_UI_FONT_FAILED_READ);
        return { };
    }

    const auto pureFonts = uiFont.get_fonts();

    UIFontPatchStream stream(fInfo);
    const auto size = static_cast<int32_t>(stream.add_fonts(pureFonts));

    if (!stream.save()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::MIGR_UI_FONT_FAILED_WRITE);
        return { 0, size, 0 };
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::MIGR_UI_FONT_RESULT, size, size, 0, 0);
    return { size, size, 0 };*/
    return { };
}

PatcherResult UIFontPatcher::extract() {
    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_UI_FONT_START);

    FilesystemUtil::delete_and_create_directories(path_t(m_dir) / UIFontPath::PATCH_BASE);

    const auto fInfo = path_t(m_dir) / UIFontPath::PATCH_FILE_FONTS_INFO;
    const auto fFiles = path_t(m_dir) / UIFontPath::PATCH_FOLDER_FONTS_FILES;

    std::filesystem::create_directories(fFiles);

    const UIFont uiFont(m_pUI);

    if (!uiFont.is_valid()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_FONT_FAILED_READ);
        return { 0, 0, 0 };
    }

    const auto pureFonts = uiFont.get_fonts();

    UIFontPatchStream stream(fInfo);

    const auto size = static_cast<int32_t>(stream.add_fonts(pureFonts));

    if (!stream.save()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_UI_FONT_FAILED_WRITE);
        return { };
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_UI_FONT_RESULT, size, size, 0, 0);
    return { size, size, 0 };
}

UIFontPatcher::UIFontPatcher(const path_t& src, std::shared_ptr<UI> pUI) :
    IPatcher(src),
    m_pUI(pUI) { }
