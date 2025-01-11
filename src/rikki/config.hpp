#ifndef RIKKY_PATCHER_RIKKI_CONFIG_HPP
#define RIKKY_PATCHER_RIKKI_CONFIG_HPP
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
     * Config config(...);
     * const char* key = "my_key";
     *
     * if (config.exists(key)) {
     *      auto value = config.get<...>(key);
     *      ...
     * }
     * @endcode
     */
    template <class T>
    T get(const char* key);

    /**
     * @brief Get json value reference using key.
     *
     * @param [in] key Target key.
     * @return Returns json reference of key.
     */
    auto& get_ref(const char* key);

    /**
     * @brief Check is key exists.
     *
     * @param [in] key Target key.
     * @return Returns true if key exists.
     */
    bool exists(const char* key) const;

    /**
     * @brief Set config value with key. If key exists, it will overwrite.
     *
     * @tparam T Value type.
     * @param [in] key Target key.
     * @param [in] value Target value.
     */
    template <class T>
    void set(const char* key, T&& value);

    /**
     * @brief Save config file.
     *
     * @return Returns true, if data saved successfully.
     */
    bool save() const;

public:
    /**
     * @brief Create or load config data from file.
     *
     * @param [in] file Target config file path.
     */
    explicit Config(const path_t& file);
private:
    const path_t m_file; /* Config file path. */
    nlohmann::json m_j;  /* Config json data */

public:
    constexpr static auto KEY_GMDIR = "gmdir"; /* Key of game directory. */
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


#endif //RIKKY_PATCHER_RIKKI_CONFIG_HPP
