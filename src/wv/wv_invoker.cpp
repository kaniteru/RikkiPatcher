#include "wv_invoker.hpp"
#include "wv_log_fmt.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/config.hpp"
#include "rikki/config_keys.hpp"

#include "utils/string_util.hpp"

// ======================== C L A S S ========================
// ===    WvInvoker
// ======================== C L A S S ========================

void WvInvoker::init_success() {
    constexpr static auto FN = "_initSuccess";
    WvInvoker::call(FN);
}

void WvInvoker::init_gmdir(const path_t& gmdir) {
    constexpr static auto FN = "_initGmdir";

    if (gmdir.empty()) {
        WvInvoker::call(FN, "");
        return;
    }

    DirMgr::init(gmdir);

    const auto u8 = gmdir.generic_u8string();
    auto u8str =  StringUtil::u8_to_cstr(u8);
    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::WV_INVOKER_SET_GM_DIR, u8str);
    Config::set(ConfigKeys::KEY_GMDIR, u8str);
    Config::save();
    WvInvoker::call(FN, u8str);
}

void WvInvoker::selected_patch_data_dir(const path_t& dir) {
    constexpr static auto FN = "_selectedPatchDataDir";

    if (dir.empty()) {
        WvInvoker::call(FN, "");
        return;
    }

    const auto u8 = dir.generic_u8string();
    //WvInvoker::log(WV_LOG_LV_INFO, u8"Loaded patch data files from " + u8);
    WvInvoker::call(FN, StringUtil::u8_to_cstr(u8));
}

void WvInvoker::finish_patch() {
    constexpr static auto FN = "_finishPatch";
    WvInvoker::call(FN);
}

void WvInvoker::clear_log() {
    constexpr static auto FN = "_clearLog";
    WvInvoker::call(FN);
}
