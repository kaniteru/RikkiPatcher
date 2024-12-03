#ifndef RIKKI_PATCHER_UTILS_JSON_UTIL_HPP
#define RIKKI_PATCHER_UTILS_JSON_UTIL_HPP
#include "precompiled.hpp"

class JsonUtil {
public:
    /**
     * @brief Load json data from file.
     *
     * @param [out] j Json instance.
     * @param [in] file Json file path.
     * @return Returns true if json file loaded successfully.
     *
     * @code
     * nlohmann::json j { };
     * bool loaded = JsonUtil::load_from_file(j, path_t(...));
     *
     * if (loaded) { ... }
     * @endcode
     */
    static bool load_from_file(nlohmann::json& j, const path_t& file);

    /**
     * @brief Load orderd json data from file.
     *
     * @param [out] j Orederd json instance.
     * @param [in] file Json file path.
     * @return Returns true if json file loaded successfully.
     *
     * @code
     * nlohmann::ordered_json j { };
     * bool loaded = JsonUtil::load_from_file(j, path_t(...));
     *
     * if (loaded) { ... }
     * @endcode
     */
    static bool load_from_file(nlohmann::ordered_json& j, const path_t& file);

    /**
     * @brief Save json data into file.
     *
     * @param [in] j Json instance.
     * @param [in] file Target file path.
     * @return Returns true if json file saved successfully.
     *
     * @code
     * nlohmann::json j { ... };
     * bool saved = JsonUtil::save_into_file(j, path_t(...));
     *
     * if (saved) { ... }
     * @endcode
     */
    static bool save_into_file(const nlohmann::json& j, const path_t& file);

     /**
     * @brief Save ordered json data into file.
     *
     * @param [in] j Ordered json instance.
     * @param [in] file Target file path.
     * @return Returns true if json file saved successfully.
     *
     * @code
     * nlohmann::ordered_json j { ... };
     * bool saved = JsonUtil::save_into_file(j, path_t(...));
     *
     * if (saved) { ... }
     * @endcode
     */
    static bool save_into_file(const nlohmann::ordered_json& j, const path_t& file);
};


#endif //RIKKI_PATCHER_UTILS_JSON_UTIL_HPP
