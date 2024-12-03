#ifndef RIKKI_PATCHER_LANG_LANG_HPP
#define RIKKI_PATCHER_LANG_LANG_HPP
#include "precompiled.hpp"

enum eLang {
    LANG_HELLO
};

class Lang {
public:
    template<typename... Args>
    std::u8string get(eLang type, Args&&... args);

public:
    Lang(const path_t& path);
private:
    nlohmann::json m_j;
};


template<typename ... Args>
inline
std::u8string Lang::get(eLang type, Args&&... args) {
}


#endif //RIKKI_PATCHER_LANG_LANG_HPP
