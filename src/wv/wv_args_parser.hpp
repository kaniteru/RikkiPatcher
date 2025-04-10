#ifndef RIKKI_PATCHER_WV_WV_ARGS_PARSER_HPP
#define RIKKI_PATCHER_WV_WV_ARGS_PARSER_HPP
#include "precompiled.hpp"

/* wv_args_parser.hpp
 *  Included structs:
 *      - WvArgsParser
 */

// ======================= S T R U C T =======================
// ===    WvArgsParser
// ======================= S T R U C T =======================

struct WvArgsParser {
    std::string get() const;

    template<class T>
    T get(size_t idx) const;

    template<class T>
    void add(T&& t);

    size_t get_count() const;

    WvArgsParser();

    template<typename... Args>
    explicit WvArgsParser(Args&&... args);

    static WvArgsParser from_js(std::string_view args);
private:
    nlohmann::json m_args;
};

template<class T>
void WvArgsParser::add(T&& t) {
    m_args.emplace_back(t);
}

template<class T>
T WvArgsParser::get(const size_t idx) const {
    return m_args[idx];
}

template<typename... Args>
WvArgsParser::WvArgsParser(Args&& ... args) {
    m_args = { std::forward<Args>(args)... };
}


#endif //RIKKI_PATCHER_WV_WV_ARGS_PARSER_HPP
