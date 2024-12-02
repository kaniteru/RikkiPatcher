#ifndef RIKKY_PATCHER_RIKKY_CONFIG_HPP
#define RIKKY_PATCHER_RIKKY_CONFIG_HPP
#include "precompiled.hpp"

class Config {
public:
    template <class T>
    T get(const char* key);

    auto& get_ref(const char* key);

    bool exists(const char* key);

    template <class T>
    void set(const char* key, T&& value);

    bool save() const;
public:
    explicit Config(const path_t& file);
private:
    const path_t m_file;
    nlohmann::json m_j;

public:
    constexpr static auto KEY_GMDIR = "gmdir";
};

template<class T>
inline
T Config::get(const char* key) {
    return m_j[key];
}

inline
auto& Config::get_ref(const char* key) {
    return m_j[key];
}

template<class T>
inline
void Config::set(const char* key, T&& value) {
    m_j[key] = value;
}


#endif //RIKKY_PATCHER_RIKKY_CONFIG_HPP
