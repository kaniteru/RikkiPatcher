#include "wv_invoker.hpp"
#include "enums.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/config.hpp"

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

    InstanceFactory::instance().reset<DirMgr>();
    InstanceFactory::instance().make<DirMgr>(gmdir);

    const auto u8 = gmdir.generic_u8string();

    const auto u8log = u8"Game directory set: " + u8;
    WvInvoker::log(LOG_LV_ALERT, reinterpret_cast<const char*>(u8log.c_str()));

    auto u8str = reinterpret_cast<const char*>(u8.c_str());

    auto config = InstanceFactory::instance().get<Config>();
    config->set(Config::KEY_GMDIR, u8str);
    config->save();

    WvInvoker::call(FN, u8str);
}

void WvInvoker::selected_patch_data_dir(const path_t& dir) {
    constexpr static auto FN = "_selectedPatchDataDir";

    if (dir.empty()) {
        WvInvoker::call(FN, "");
        return;
    }

    const auto u8 = dir.generic_u8string();

    const auto u8log = u8"Loaded patch data files from " + u8;
    WvInvoker::log(LOG_LV_INFO, reinterpret_cast<const char*>(u8log.c_str()));

    auto u8str = reinterpret_cast<const char*>(u8.c_str());
    WvInvoker::call(FN, u8str);
}

void WvInvoker::finish_patch() {
    constexpr static auto FN = "_finishPatch";
    WvInvoker::call(FN);
}

void WvInvoker::log(enum eLogLV lv, std::string_view msg) {
    constexpr static auto FN = "_log";
    WvInvoker::call(FN, lv, msg);
}

void WvInvoker::clear_log() {
    constexpr static auto FN = "_clearLog";
    WvInvoker::call(FN);
}
