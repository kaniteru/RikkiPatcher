#include "wv_binder.hpp"
#include "wv_invoker.hpp"
#include "wv_args_parser.hpp"
#include "wv_log_fmt.hpp"

#include "rikki/config.hpp"
#include "rikki/config_keys.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/dir_mgr_enum.hpp"
#include "rikki/patcher/patcher.hpp"

#include "utils/logger.hpp"
#include "utils/string_util.hpp"
#include "utils/dialog_util.hpp"
#include "utils/filesystem_util.hpp"
#include "utils/json_util.hpp"
#include "utils/registry_reader.hpp"

#define HANDLER_ARGS       const std::string& args
#define HANDLER_ARGS_UNREF const std::string&
#define ASYNC_HANDLER_ARGS const std::string& id, const std::string& args, void* a3

namespace {
std::string init_patcher(HANDLER_ARGS_UNREF) {
    WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::WV_BINDER_INIT_START);
    path_t gmDir { };

    try {
        if (Config::exists(ConfigKeys::KEY_GMDIR)) {
            const auto s = Config::get<std::string>(ConfigKeys::KEY_GMDIR);
            gmDir = StringUtil::str_to_u8(s);
        }
    }
    catch (const nlohmann::json::exception& e) {
        LOG_FATAL("Failed to load the gmdir from config: {}", e.what());
    }

    WvInvoker::init_gmdir(gmDir);
    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::WV_BINDER_INIT_SUCCESS);
    WvInvoker::init_success();
    return { };
}

std::string request_trans(HANDLER_ARGS_UNREF) {
    std::u8string rtn = u8"[";

    const auto files = FilesystemUtil::sort_files(DirMgr::get(DIR_PROJ_LANG));
    const auto size = files.size();

    for (uint32_t i = 0; i < size; i++) {
        const auto fName = files[i].filename().replace_extension("").u8string();
        nlohmann::json j { };

        try {
            if (!JsonUtil::load_from_file(j, files[i])) {
                LOG_FATAL("Failed to load json file: {}", files[i].generic_u8string());
                continue;
            }
        }
        catch (const nlohmann::json::exception& e) {
            LOG_FATAL("Failed to parse json file: {} -> {}", files[i].generic_u8string(), e.what());
            continue;
        }

        // ["lang", json]
        rtn += u8"[\"" + fName + u8"\", " + StringUtil::str_to_u8(j.dump()) + u8"]";

        if (i  + 1 < size) {
            rtn += u8", ";
        }
    }

    rtn += u8"]";
    return StringUtil::u8_to_str(rtn);
}

std::string open_github(HANDLER_ARGS_UNREF) {
    constexpr static auto URL = L"https://github.com/kaniteru/RikkiPatcher";
    ShellExecute(nullptr, nullptr, URL, nullptr, nullptr, SW_HIDE);
    return { };
}

std::string open_project_web(HANDLER_ARGS_UNREF) {
    constexpr static auto URL = L"https://kaniteru.github.io/project/rikkipatcher/index.html?section=usage";
    ShellExecute(nullptr, nullptr, URL, nullptr, nullptr, SW_HIDE);
    return { };
}

std::string set_gmdir_manually(HANDLER_ARGS_UNREF) {
    path_t dir { };

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::WV_BINDER_DIALOG_GMDIR_NOTICE);

    if (!DialogUtil::folder_select_dialog(dir)) {
        // maybe a user closed the dialog window
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::WV_BINDER_DIALOG_FAILED);
    }

    WvInvoker::init_gmdir(dir);
    return { };
}

std::string set_gmdir_automatically(HANDLER_ARGS_UNREF) {
    constexpr static auto REG_STEAM          = L"SOFTWARE\\Valve\\Steam";
    constexpr static auto KEY_STEAM_PATH     = L"SteamPath";

    constexpr static auto REG_GAME           = L"SOFTWARE\\Valve\\Steam\\Apps\\3269960";
    constexpr static auto KEY_GAME_INSTALLED = L"Installed";
    constexpr static auto KEY_GAME_NAME      = L"Name";

    constexpr static auto GAME_DATA_FOLDER_NAME = u8"鼓手余命十日谭";

    RegistryReader rrSteam(REG_STEAM);

    if (!rrSteam.is_valid()) {
        LOG_FATAL("RegistryReader can't open:  {}", StringUtil::wstr_to_str(REG_STEAM));
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::WV_BINDER_GMDIR_AUTO_FAILED_FIND_STEAM);
        WvInvoker::init_gmdir({ });
        return { };
    }

    path_t dir = rrSteam.read_string(KEY_STEAM_PATH);

    if (dir.empty()) {
        LOG_FATAL("RegistryReader can't read key: {}", StringUtil::wstr_to_str(KEY_STEAM_PATH));
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::WV_BINDER_GMDIR_AUTO_FAILED_FIND_STEAM);
        WvInvoker::init_gmdir({ });
        return { };
    }

    const auto u8dir = dir.generic_u8string();
    WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::WV_BINDER_GMDIR_AUTO_OK_STEAM_DIR, StringUtil::u8_to_cstr(u8dir));

    RegistryReader rrGame(REG_GAME);

    if (!rrGame.is_valid()) {
        LOG_FATAL("RegistryReader can't open:  {}", StringUtil::wstr_to_str(REG_GAME));
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::WV_BINDER_GMDIR_AUTO_FAILED_FIND_GAME_FROM_STEAM);
        WvInvoker::init_gmdir({ });
        return { };
    }

    if (const auto installed = rrGame.read_dword(KEY_GAME_INSTALLED); installed == 0) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::WV_BINDER_GMDIR_AUTO_FAILED_GAME_NOT_INSTALLED);
        WvInvoker::init_gmdir({ });
        return { };
    }

    WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::WV_BINDER_GMDIR_AUTO_OK_GAME_INSTALLED);

    /*const auto gm = rrGame.read_string(KEY_GAME_NAME);

    if (gm.empty()) {
        LOG_FATAL("RegistryReader can't read key:  {}", StringUtil::wstr_to_str(KEY_GAME_NAME));
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::WV_BINDER_GMDIR_AUTO_FAILED_FIND_GAME_NAME);
        WvInvoker::init_gmdir({ });
        return { };
    }

    WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::WV_BINDER_GMDIR_AUTO_OK_GAME_NAME);*/

    dir.append("steamapps").append("common").append(GAME_DATA_FOLDER_NAME).append(GAME_DATA_FOLDER_NAME);

    if (!fs::exists(dir)) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::WV_BINDER_GMDIR_AUTO_FAILED_GAME_DIR_NOT_EXISTS);
        WvInvoker::init_gmdir({ });
        return { };
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::WV_BINDER_GMDIR_AUTO_OK_GAME_DIR);
    WvInvoker::init_gmdir(dir);
    return { };
}

std::string select_patch_data_dir(HANDLER_ARGS_UNREF) {
    path_t dir { };

    if (!DialogUtil::folder_select_dialog(dir)) {
        // maybe a user closed the dialog window
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::WV_BINDER_DIALOG_FAILED);
    }

    WvInvoker::selected_patch_data_dir(dir);
    return { };
}

std::string patch_extract(HANDLER_ARGS_UNREF) {
    const auto dst = DirMgr::get(DIR_PROJ_DATA_EXTRACED);

    const Patcher patcher(dst);
    patcher.do_extract();

    const auto u8dst = dst.generic_u8string();
    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::WV_BINDER_EXTRACT_RESULT, StringUtil::u8_to_cstr(u8dst));
    WvInvoker::finish_patch();
    return { };
}

std::string patch_apply(HANDLER_ARGS) {
    const auto a = WvArgsParser::from_js(args);
    const auto src = a.get<std::string>(0);
    const path_t u8src(StringUtil::str_to_u8(src));

    const Patcher patcher(u8src);
    patcher.do_patch();

    WvInvoker::finish_patch();
    return { };
}

std::string migrate_patch_data(HANDLER_ARGS_UNREF) {
    if (path_t dir { }; DialogUtil::folder_select_dialog(dir)) {
        const Patcher patcher(dir);
        patcher.do_migration();
    } else {
        // maybe a user closed the dialog window
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::WV_BINDER_DIALOG_FAILED);
    }

    WvInvoker::finish_patch();
    return { };
}
} //namespace

// ======================== C L A S S ========================
// ===    WvBinder
// ======================== C L A S S ========================

#define BIND_EVENT_HANDLER(EVENT, FN)       m_wv->bind(EVENT, [](HANDLER_ARGS)       { return FN(args); });
#define BIND_ASYNC_EVENT_HANDLER(EVENT, FN) m_wv->bind(EVENT, [](ASYNC_HANDLER_ARGS) { FN(id, args, pArgs); }, nullptr);

void WvBinder::bind() const {
    LOG_INFO("Binding wv events...");

    BIND_EVENT_HANDLER("INIT_PATCHER",            init_patcher);
    BIND_EVENT_HANDLER("REQUEST_TRANS",           request_trans);
    BIND_EVENT_HANDLER("OPEN_GITHUB",             open_github);
    BIND_EVENT_HANDLER("OPEN_PROJECT_WEB",        open_project_web);
    BIND_EVENT_HANDLER("SET_GMDIR_MANUALLY",      set_gmdir_manually);
    BIND_EVENT_HANDLER("SET_GMDIR_AUTOMATICALLY", set_gmdir_automatically);
    BIND_EVENT_HANDLER("SELECT_PATCH_DATA_DIR",   select_patch_data_dir);
    BIND_EVENT_HANDLER("PATCH_EXTRACT",           patch_extract);
    BIND_EVENT_HANDLER("PATCH_APPLY",             patch_apply);
    BIND_EVENT_HANDLER("MIGRATE_PATCH_DATA",      migrate_patch_data);

    LOG_INFO("All events bound");
}
