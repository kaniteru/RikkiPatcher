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
     * @param key Configuration key.
     * @return Value of a specified type.
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
    template <class T> [[nodiscard]]
    static T get(const char* key);

    /**
     * @brief Get json value reference using key.
     *
     * @param key Target key.
     * @return Returns json reference of a key.
     */
    [[nodiscard]]
    static auto& get_ref(const char* key);

    /**
     * @brief Check is key exists.
     *
     * @param key Configuration key.
     * @return Returns true if the key exists.
     */
    [[nodiscard]]
    static bool exists(const char* key);

    /**
     * @brief Set the config value with a key. If a key exists, it will overwrite.
     *
     * @tparam T Value type.
     * @param key Configuration key.
     * @param [in] value Target value.
     */
    template <class T>
    static void set(const char* key, T&& value);

    /**
     * @brief Save the config file.
     *
     * @return true if data saved successfully.
     */
    static bool save();

    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

private:
    static Config& instance();

    Config();
    ~Config();
private:
    mutable std::shared_mutex m_mtx;
    nlohmann::json m_j; /* Config json data */
};

template<class T>
T Config::get(const char* key) {
    std::shared_lock lock(Config::instance().m_mtx);
    return Config::instance().m_j[key];
}

inline
auto& Config::get_ref(const char* key) {
    std::lock_guard lock(Config::instance().m_mtx);
    return Config::instance().m_j[key];
}

template<class T>
void Config::set(const char* key, T&& value) {
    std::lock_guard lock(Config::instance().m_mtx);
    Config::instance().m_j[key] = value;
}


#endif //RIKKI_PATCHER_RIKKI_CONFIG_HPP
