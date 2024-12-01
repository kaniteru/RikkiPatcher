#include "wv_invoker.hpp"
#include "enums.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/config.hpp"
#include "utils/string_util.hpp"

void WvInvoker::init_success() {
    constexpr static auto FN = "_initSuccess";
    WvInvoker::call(FN);
}

void WvInvoker::init_gmdir(const path_t gmdir) {
    constexpr static auto FN = "_initGmdir";

    if (gmdir.empty()) {
        WvInvoker::call(FN, "");
        return;
    }

    auto& instFac = InstanceFactory::instance();
    instFac.reset<DirMgr>();
    instFac.make<DirMgr>(gmdir);

    const auto u8 = gmdir.generic_u8string();
    WvInvoker::log(LOG_LV_ALERT, u8"Game directory set: " + u8);

    auto pConfig = instFac.get<Config>();
    auto u8str =  StringUtil::u8_to_cstr(u8);
    pConfig->set(Config::KEY_GMDIR, u8str);
    pConfig->save();
    WvInvoker::call(FN, u8str);
}

void WvInvoker::selected_patch_data_dir(const path_t& dir) {
    constexpr static auto FN = "_selectedPatchDataDir";

    if (dir.empty()) {
        WvInvoker::call(FN, "");
        return;
    }

    const auto u8 = dir.generic_u8string();
    WvInvoker::log(LOG_LV_INFO, u8"Loaded patch data files from " + u8);
    WvInvoker::call(FN, StringUtil::u8_to_cstr(u8));
}

void WvInvoker::finish_patch() {
    constexpr static auto FN = "_finishPatch";
    WvInvoker::call(FN);
}

void WvInvoker::log(enum eLogLV lv, std::string_view msg) {
    constexpr static auto FN = "_log";
    WvInvoker::call(FN, lv, msg);
}

void WvInvoker::log(eLogLV lv, std::u8string_view msg) {
    constexpr static auto FN = "_log";
    WvInvoker::call(FN, lv, reinterpret_cast<const char*>(msg.data()));
}

void WvInvoker::clear_log() {
    constexpr static auto FN = "_clearLog";
    WvInvoker::call(FN);
}
