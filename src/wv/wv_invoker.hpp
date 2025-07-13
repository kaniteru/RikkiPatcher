#ifndef RIKKI_PATCHER_WV_WV_INVOKER_HPP
#define RIKKI_PATCHER_WV_WV_INVOKER_HPP
#include "precompiled.hpp"
#include "wv_mgr.hpp"
#include "wv_args_parser.hpp"

#include "utils/logger.hpp"
#include "utils/string_util.hpp"

enum eWvLogLv {
    WV_LOG_LV_INFO   = 0,
    WV_LOG_LV_ALERT  = 1,
    WV_LOG_LV_PROG    = 2,
    WV_LOG_LV_FATAL = 3,
    WV_LOG_LV_DEBUG = 4
};

// ======================== C L A S S ========================
// ===    WvInvoker
// ======================== C L A S S ========================

class WvInvoker {
public:
    template<typename... Args>
    static webview::noresult call(std::string_view func, Args&&... args);

    static void init_success();

    static void init_gmdir(const path_t& gmdir);

    static void selected_patch_data_dir(const path_t& dir);

    static void finish_patch();

    template <typename... Args>
    static void log(eWvLogLv lv, std::string_view fmt, Args&&... args);

    template <typename... Args>
    static void log(eWvLogLv lv, std::u8string_view fmt, Args&&... args);

    static void clear_log();
};

template<typename... Args>
webview::noresult WvInvoker::call(const std::string_view func, Args&&... args) {
    const WvArgsParser parser(args...);
    const std::string cmd = std::string(func) + "(" + parser.get() + ");";
    const auto u8cmd = StringUtil::str_to_u8(cmd);
    const auto js = StringUtil::u8_to_cstr(u8cmd);
    LOG(VERBOSE, "execute js: {}", cmd);
    return WvMgr::get()->eval(js);
}

template<typename ... Args>
void WvInvoker::log(eWvLogLv lv, const std::string_view fmt, Args&&... args) {
    constexpr static auto FN = "_log";
    WvInvoker::call(FN, lv, fmt, args...);
}

template<typename ... Args>
void WvInvoker::log(eWvLogLv lv, const std::u8string_view fmt, Args&&... args) {
    constexpr static auto FN = "_log";
    WvInvoker::call(FN, lv, StringUtil::u8_to_cstr(fmt), args...);
}


#endif //RIKKI_PATCHER_WV_WV_INVOKER_HPP
