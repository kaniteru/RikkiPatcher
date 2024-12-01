#ifndef RIKKI_PATCHER_WV_WV_INVOKER_HPP
#define RIKKI_PATCHER_WV_WV_INVOKER_HPP
#include "precompiled.hpp"
#include "wv_args_parser.hpp"
#include "utils/instance_factory.hpp"

enum eLogLV;

class WvInvoker {
public:
    template<typename... Args>
    static webview::noresult call(std::string_view func, Args&&... args);

    static void init_success();
    static void init_gmdir(const path_t gmdir);

    static void selected_patch_data_dir(const path_t& dir);

    static void finish_patch();

    static void log(eLogLV lv, std::string_view msg);
    static void log(eLogLV lv, std::u8string_view msg);
    static void clear_log();
};

template<typename... Args>
webview::noresult WvInvoker::call(std::string_view func, Args&& ... args) {
    WvArgsParser parser(args...);
    std::string str = std::string(func) + "(" + parser.get() + ");";
    //std::cout << "str: " << str << std::endl;

    auto u8str = reinterpret_cast<const char8_t*>(str.c_str());
    auto js = reinterpret_cast<const char*>(u8str);
    //std::cout << "js: " << js << std::endl;
    return InstanceFactory::instance().get<webview::webview>()->eval(js);
}


#endif //RIKKI_PATCHER_WV_WV_INVOKER_HPP
