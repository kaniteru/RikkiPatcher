#ifndef RIKKI_PATCHER_RIKKI_CONFIG_HPP
#define RIKKI_PATCHER_RIKKI_CONFIG_HPP
#include "precompiled.hpp"

/* config.hpp
 *  Included classes:
 *      - Config
 */

// ======================== C L A S S ========================
// ===    Config
// ======================== C L A S S ========================

/**
 * @brief Using get or set the project settings.
 */
class Config {
public:
    /**
     * @brief Get config value using key.
     *
     * @tparam T Value type.
     * @param [in] key Target key.
     * @return Returns value of key.
     *
     * @code
     * const char* key = "my_key";
     *
     * if (config::exists(key)) {
     *      auto value = config::get<...>(key);
     *      ...
     * }
     * @endcode
     */
    template <class T>
    static T get(const char* key);

    /**
     * @brief Get json value reference using key.
     *
     * @param [in] key Target key.
     * @return Returns json reference of key.
     */
    static auto& get_ref(const char* key);

    /**
     * @brief Check is key exists.
     *
     * @param [in] key Target key.
     * @return Returns true if key exists.
     */
    static bool exists(const char* key);

    /**
     * @brief Set config value with key. If key exists, it will overwrite.
     *
     * @tparam T Value type.
     * @param [in] key Target key.
     * @param [in] value Target value.
     */
    template <class T>
    static void set(const char* key, T&& value);

    /**
     * @brief Save config file.
     *
     * @return Returns true, if data saved successfully.
     */
    static bool save();

private:
    static Config& instance();

    Config();
    ~Config();
private:
    nlohmann::json m_j;  /* Config json data */
    std::shared_mutex m_mtx;
};

template<class T>
T Config::get(const char* key) {
    std::shared_lock lock(Config::instance().m_mtx);
    return Config::instance().m_j[key];
}

inline
auto& Config::get_ref(const char* key) {
    std::unique_lock lock(Config::instance().m_mtx);
    return Config::instance().m_j[key];
}

template<class T>
void Config::set(const char* key, T&& value) {
    std::unique_lock lock(Config::instance().m_mtx);
    Config::instance().m_j[key] = value;
}


#endif //RIKKI_PATCHER_RIKKI_CONFIG_HPP
