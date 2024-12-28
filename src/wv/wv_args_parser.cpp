#include "wv_args_parser.hpp"

std::string WvArgsParser::get() const {
    if (this->get_count() < 1) {
        return { };
    }

    const auto dump = m_args.dump();
    return dump.substr(1, dump.length() - 2);
}

size_t WvArgsParser::get_count() const {
    return m_args.size();
}

WvArgsParser::WvArgsParser() = default;

WvArgsParser WvArgsParser::from_js(std::string_view args) {
    WvArgsParser result { };
    result.m_args = nlohmann::json::parse(args);
    return result;
}
