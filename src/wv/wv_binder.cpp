#include "wv_binder.hpp"
#include "utils/instance_factory.hpp"
#include "wv_args_parser.hpp"
#include "wv_invoker.hpp"
#include "enums.hpp"
#include "rikki/config.hpp"
#include "utils/worker.hpp"
#include "rikki/dir_mgr.hpp"
#include "utils/dialog_util.hpp"
#include "utils/registry_reader.hpp"
#include "rikki/patcher.hpp"

#define BIND_EVENT_HANDLER(EVENT, FN) InstanceFactory::instance().get<webview::webview>()->bind(EVENT, [this](HANDLER_ARGS) { return FN(args); });
#define BIND_ASYNC_EVENT_HANDLER(EVENT, FN) InstanceFactory::instance().get<webview::webview>()->bind(EVENT, [this](ASYNC_HANDLER_ARGS) { FN(id, args, pArgs); }, nullptr);

void WvBinder::bind() {
    BIND_EVENT_HANDLER("INIT_PATCHER", this->init_patcher);
    BIND_EVENT_HANDLER("OPEN_GITHUB", this->open_github);
    BIND_EVENT_HANDLER("SET_GMDIR_MANUALLY", this->set_gmdir_manually);
    BIND_EVENT_HANDLER("SET_GMDIR_AUTOMATICALLY", this->set_gmdir_automatically);
    BIND_EVENT_HANDLER("SELECT_PATCH_DATA_DIR", this->select_patch_data_dir);
    BIND_EVENT_HANDLER("PATCH_EXTRACT", this->patch_extract);
    BIND_EVENT_HANDLER("PATCH_APPLY", this->patch_apply);
}

std::string WvBinder::init_patcher(HANDLER_ARGS) {
    constexpr static auto CONFIG_FILE = "config.json";
    constexpr static auto WORKER_THREADS = 2;

    WvInvoker::log(LOG_LV_PROG, "initializing patcher...");

    auto& inst = InstanceFactory::instance();
    inst.make<Config>(std::filesystem::current_path().append(CONFIG_FILE));
    inst.make<Worker>(WORKER_THREADS);

    path_t gmDir { };

    try {
        if (auto pConfig = inst.get<Config>(); pConfig->exists(Config::KEY_GMDIR)) {
            auto s = pConfig->get<std::string>(Config::KEY_GMDIR);
            gmDir = reinterpret_cast<const char8_t*>(s.c_str());
        }
    }
    catch (const nlohmann::json::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    auto pWorker = inst.get<Worker>();
    pWorker->start();

    WvInvoker::log(LOG_LV_INFO, "Patcher initialized");

    WvInvoker::init_gmdir(gmDir);
    WvInvoker::init_success();
    return { };
}

std::string WvBinder::open_github(HANDLER_ARGS) {
    constexpr static auto URL = L"https://github.com/kaniteru/RikkiPatcher";
    ShellExecute(nullptr, nullptr, URL, nullptr, nullptr, SW_SHOW);
    return { };
}

std::string WvBinder::set_gmdir_manually(HANDLER_ARGS) {
    path_t dir { };

    WvInvoker::log(LOG_LV_ALERT, "Please select the folder containing the game executable (.exe) file");

    if (!DialogUtil::folder_select_dialog(dir)) {
        WvInvoker::log(LOG_LV_ERR, "An error occurred while retrieving the path");
    }

    WvInvoker::init_gmdir(dir);
    return { };
}

std::string WvBinder::set_gmdir_automatically(HANDLER_ARGS) {
    constexpr static auto REG_STEAM   = L"SOFTWARE\\Valve\\Steam";
    constexpr static auto KEY_STEAM_PATH = L"SteamPath";

    constexpr static auto REG_GAME = L"SOFTWARE\\Valve\\Steam\\Apps\\3269960";
    constexpr static auto KEY_GAME_INSTALLED = L"Installed";
    constexpr static auto KEY_GAME_NAME = L"Name";

    constexpr static auto GAME_DATA_FOLDER_NAME = u8"鼓手余命十日谭";

    RegistryReader rrSteam(REG_STEAM);
    path_t dir { };

    if (!rrSteam.is_valid()) {
        std::wcerr << "RegisterReader can't open:  " << REG_STEAM << std::endl;
        WvInvoker::log(LOG_LV_ERR, "Can't find steam");
        WvInvoker::init_gmdir(dir);
        return { };
    }

    path_t steam = rrSteam.read_string(KEY_STEAM_PATH);

    if (steam.empty()) {
        std::wcerr << "RegistryReader can't read key: " << KEY_STEAM_PATH << std::endl;
        WvInvoker::log(LOG_LV_ERR, "Can't find steam");
        WvInvoker::init_gmdir(dir);
        return { };
    }
    else {
        dir = steam;
        const auto u8log = u8"Found steam directory: " + dir.u8string();
        auto cstr = reinterpret_cast<const char*>(u8log.c_str());
        WvInvoker::log(LOG_LV_PROG, cstr);
    }

    RegistryReader rrGame(REG_GAME);

    if (!rrGame.is_valid()) {
        std::wcerr << "RegisterReader can't open:  " << REG_GAME << std::endl;
        WvInvoker::log(LOG_LV_ERR, "Can't find installed game in steam");
        WvInvoker::init_gmdir(dir);
        return { };
    }

    if (auto installed = rrGame.read_dword(KEY_GAME_INSTALLED); installed == 0) {
        WvInvoker::log(LOG_LV_ERR, "Game doesn't installed");
        WvInvoker::init_gmdir(dir);
        return { };
    }
    else {
        WvInvoker::log(LOG_LV_PROG, "Checked game installed");
    }

    auto gm = rrGame.read_string(KEY_GAME_NAME);

    if (gm.empty()) {
        std::wcerr << "RegistryReader can't read key: " << KEY_GAME_NAME << std::endl;
        WvInvoker::log(LOG_LV_ERR, "Can't find installed game name");
        WvInvoker::init_gmdir(dir);
        return { };
    }
    else {
        WvInvoker::log(LOG_LV_PROG, "Checked game folder name");
    }

    dir.append("steamapps").append("common").append(gm).append(GAME_DATA_FOLDER_NAME);

    if (!std::filesystem::exists(dir)) {
        WvInvoker::log(LOG_LV_ERR, "Game directory doesn't exits");
        dir = path_t();
    }
    else {
        WvInvoker::log(LOG_LV_INFO, "Found game directory");
    }

    WvInvoker::init_gmdir(dir);
    return { };
}

std::string WvBinder::select_patch_data_dir(const std::string& args) {
    path_t dir { };

    if (!DialogUtil::folder_select_dialog(dir)) {
        WvInvoker::log(LOG_LV_ERR, "An error occurred while retrieving the path");
    }

    WvInvoker::selected_patch_data_dir(dir);
    return { };
}

std::string WvBinder::patch_extract(HANDLER_ARGS) {
    auto pDirMgr = InstanceFactory::instance().get<DirMgr>();
    auto src = pDirMgr->get(DIR_GAME_JSON_DIALOGUES);
    auto dst = pDirMgr->get(DIR_PROJ_DATA_EXTRACED);

    Extractor::extract_dialogues(src, dst);
    WvInvoker::finish_patch();
    return { };
}

std::string WvBinder::patch_apply(HANDLER_ARGS) {
    auto a = WvArgsParser::from_js(args);
    auto src = a.get<std::string>(0);
    auto u8src = reinterpret_cast<const char8_t*>(src.c_str());

    Patcher::load_and_patch(u8src);
    WvInvoker::finish_patch();
    return { };
}
