#include "precompiled.hpp"
#include "utils/instance_factory.hpp"
#include "wv/wv_binder.hpp"

int main(const int argc, char* argv[]) {
    const bool enableF12 = argc > 1;
    auto& instFac = InstanceFactory::instance();

    if (!instFac.make<webview::webview>(enableF12, nullptr)) {
        return EXIT_FAILURE;
    }

    const auto wv = instFac.get<webview::webview>();
    wv->set_title("Rikki Patcher");
    wv->set_size(600, 750, WEBVIEW_HINT_NONE);

    WvBinder binder { };
    binder.bind();

    const auto index = std::filesystem::current_path().append("index.html");
    wv->navigate(index.string());
    wv->run();
    return EXIT_SUCCESS;
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    return main(__argc, __argv);
}
