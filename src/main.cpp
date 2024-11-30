#include "precompiled.hpp"
#include "utils/instance_factory.hpp"
#include "wv/wv_binder.hpp"

int main(int argc, char* argv[]) {
    const bool enableF12 = argc > 1;

    if (!InstanceFactory::instance().make<webview::webview>(enableF12, nullptr)) {
        return EXIT_FAILURE;
    }

    auto wv = InstanceFactory::instance().get<webview::webview>();
    wv->set_title("Rikky Patcher");
    wv->set_size(600, 750, WEBVIEW_HINT_NONE);

    WvBinder binder;
    binder.bind();

    const auto index = std::filesystem::current_path().append("index.html");
    wv->navigate(index.string());
    wv->run();
    return EXIT_SUCCESS;
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    return main(__argc, __argv);
}
