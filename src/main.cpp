#include "precompiled.hpp"
#include "utils/logger.hpp"
#include "wv/wv_mgr.hpp"
#include "wv/wv_binder.hpp"

int rikki_main() {
    WvMgr::init(
#ifndef NDEBUG
    true
#endif
    );

    LOG_DEBUG("Running RP in debug mode, enabled f12");

    const auto wv = WvMgr::get();
    wv->set_title("Rikki Patcher");
    wv->set_size(600, 750, WEBVIEW_HINT_NONE);

    LOG_INFO("Initializing WvBinder");
    WvBinder(wv.get()).bind();

    const auto index = fs::current_path().append("index.html");

    if (!fs::exists(index)) {
        LOG_FATAL("index.html not found");
        throw std::exception("index.html not found");
    }

    LOG_DEBUG("Navigating to index.html");
    wv->navigate(index.string());
    LOG_DEBUG("Running wv client");
    wv->run();
    return EXIT_SUCCESS;
}

#ifdef NDEBUG
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
#else
int main(int, char*[]) {
#endif //NDEBUG
    try {
        return rikki_main();
    }
    catch (const webview::exception& e) {
        LOG_FATAL("Unhandled webview exception: {}", e.what());
        MessageBoxA(nullptr, e.what(), "Webview Error", MB_OK | MB_ICONERROR);
    }
    catch (const std::exception& e) {
        LOG_FATAL("Unhandled exception: {}", e.what());
        MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
    }

    return EXIT_FAILURE;
}
