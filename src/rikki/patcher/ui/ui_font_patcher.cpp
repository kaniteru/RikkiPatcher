#include "ui_font_patcher.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/data/data_path.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/ui_font/ui_font.hpp"
#include "rikki/data/ui_font/ui_font_json.hpp"
#include "rikki/stream/ui_font_patch_stream.hpp"

#include "utils/string_util.hpp"
#include "utils/instance_factory.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    UIFontPatcher
// ======================== C L A S S ========================

PatcherResult UIFontPatcher::patch() {
    PatcherResult result { };
    size_t& total   =  result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

    const auto fInfo = path_t(m_dir) / UIFontPath::PATCH_FILE_FONTS_INFO;
    const auto fFiles = path_t(m_dir) / UIFontPath::PATCH_FOLDER_FONTS_FILES;

    UIFontPatchStream stream(fInfo);

    if (!stream.is_loaded()) {
        return { };
    }

    const auto fonts = stream.get_fonts();

    UIFont uiFont(m_pUI);
    uiFont.set_fonts(fonts);

    if (!stream.save()) {
        WvInvoker::log(LOG_LV_ERR, u8"Can't save the " + fInfo.filename().u8string());
        return { };
    }

    const auto fGm = INSTFAC(DirMgr)->get(DIR_GAME_FONTS);
    std::filesystem::copy(fFiles, fGm, std::filesystem::copy_options::overwrite_existing);

    const auto size = fonts.size();
    total += size;
    ok     += size;

    const std::string log = "Total: " + std::to_string(total)      + " | ok: " + std::to_string(ok)
                                     + " | failed: " + std::to_string(failed) + " | passed: " + std::to_string(passed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult UIFontPatcher::migration() {
    PatcherResult result { };
    size_t& total   =  result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;
    size_t& passed = result.m_passed;

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

    total += size;
    ok     += size;
    return result;
}

PatcherResult UIFontPatcher::generate_migration_info() {
    WvInvoker::log(LOG_LV_WARN, "ui-font doesn't support generate the migration info");
    return { };
}

UIFontPatcher::UIFontPatcher(const path_t& src, UI* pUI) :
    IPatcher(src),
    m_pUI(pUI) { }
