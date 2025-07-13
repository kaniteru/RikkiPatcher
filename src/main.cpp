#include "precompiled.hpp"
#include "exception/rixception.hpp"
#include "utils/logger.hpp"
#include "wv/wv_mgr.hpp"
#include "wv/wv_binder.hpp"

int rikki_main() {
    WvMgr::init(
#ifndef NDEBUG
    true
#endif
    );

    DLOG("Running RP in debug mode, enabled f12");

    const auto wv = WvMgr::get();
    wv->set_title("Rikki Patcher");
    wv->set_size(600, 750, WEBVIEW_HINT_NONE);

    LOG(INFO, "Initializing WvBinder");
    WvBinder binder { };
    binder.bind();

    const auto index = fs::current_path().append("index.html");

    if (!fs::exists(index)) {
        LOG(FATAL, "index.html not found");
        throw ResourceRixception("index.html not found");
    }

    DLOG("Navigating to index.html");
    wv->navigate(index.string());
    DLOG("Running wv client");
    wv->run();
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    try {
        return rikki_main();
    }
    catch (const Rixception& e) {
        LOG(FATAL, "Unhandled Rixception: {}", e.what());
        MessageBoxA(nullptr, e.what(), "Rikki Patcher Error", MB_OK | MB_ICONERROR);
    }
    catch (const webview::exception& e) {
        LOG(FATAL, "Unhandled webview exception: {}", e.what());
        MessageBoxA(nullptr, e.what(), "Webview Error", MB_OK | MB_ICONERROR);
    }
    catch (const std::exception& e) {
        LOG(FATAL, "Unhandled exception: {}", e.what());
        MessageBoxA(nullptr, e.what(), "Unknown Error", MB_OK | MB_ICONERROR);
    }

    return EXIT_FAILURE;
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    return main(__argc, __argv);
}
