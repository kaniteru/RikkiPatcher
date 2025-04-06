#include "precompiled.hpp"
#include "utils/logger.hpp"
#include "wv/wv_mgr.hpp"
#include "wv/wv_binder.hpp"

int main(const int argc, char* argv[]) {
    const bool enableF12 = argc > 1;

    if (enableF12) {
        DLOG("Running RP in debug mode, enabled f12");
    }

    WvMgr::init(enableF12);
    const auto wv = WvMgr::get();
    wv->set_title("Rikki Patcher");
    wv->set_size(600, 750, WEBVIEW_HINT_NONE);

    LOG(INFO, "Initializing WvBinder");
    WvBinder binder { };
    binder.bind();

    const auto index = fs::current_path().append("index.html");

    if (!fs::exists(index)) {
        LOG(FATAL, "index.html not found");
        return EXIT_FAILURE;
    }

    DLOG("Navigating to index.html");
    wv->navigate(index.string());
    DLOG("Running wv client");
    wv->run();
    return EXIT_SUCCESS;
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    return main(__argc, __argv);
}
