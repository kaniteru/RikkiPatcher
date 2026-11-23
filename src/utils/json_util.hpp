#ifndef RIKKI_PATCHER_UTILS_JSON_UTIL_HPP
#define RIKKI_PATCHER_UTILS_JSON_UTIL_HPP
#include "precompiled.hpp"

#define ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(Type, ...)  \
friend void to_json(nlohmann::ordered_json& nlohmann_json_j, const Type& nlohmann_json_t)   { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_TO, __VA_ARGS__)) } \
friend void from_json(const nlohmann::ordered_json& nlohmann_json_j, Type& nlohmann_json_t) { NLOHMANN_JSON_EXPAND(NLOHMANN_JSON_PASTE(NLOHMANN_JSON_FROM, __VA_ARGS__)) }

/* json_util.hpp
 *  Included classes:
 *      - JsonUtil
 */

// ======================== C L A S S ========================
// ===    JsonUtil
// ======================== C L A S S ========================

class JsonUtil {
public:
    /**
     * @brief Load json data from a file.
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
     * @brief Save json data into a file.
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
     * @brief Save ordered json data into a file.
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

    /**
     * @brief Deserialize a value of type @p T from a JSON object.
     *
     * @tparam T Destination type (must be compatible with nlohmann::json::get<T>()).
     * @param j Source JSON.
     * @return Deserialized value.
     *
     * @code
     * nlohmann::json j { ... };
     * MyType v = JsonUtil::from_json<MyType>(j);
     * @endcode
     */
    template <class T>
    static T from_json(const nlohmann::json& j);

    /**
     * @brief Deserialize a value of type @p T from an ordered JSON object.
     *
     * @tparam T Destination type (must be compatible with nlohmann::ordered_json::get<T>()).
     * @param j Source ordered JSON.
     * @return Deserialized value.
     *
     * @code
     * nlohmann::ordered_json oj { ... };
     * MyType v = JsonUtil::from_json<MyType>(oj);
     * @endcode
     */
    template <class T>
    static T from_json(const nlohmann::ordered_json& j);

    /**
     * @brief Serialize a value of type @p T into a JSON object.
     *
     * @tparam T Source type (must be compatible with nlohmann::json assignment).
     * @param[out] j Destination JSON.
     * @param t Value to serialize.
     *
     * @code
     * nlohmann::json j { };
     * JsonUtil::to_json(j, value);
     * @endcode
     */
    template <class T>
    static void to_json(nlohmann::json& j, const T& t);

    /**
     * @brief Serialize a value of type @p T into an ordered JSON object.
     *
     * @tparam T Source type (must be compatible with nlohmann::ordered_json assignment).
     * @param[out] j Destination ordered JSON.
     * @param t Value to serialize.
     *
     * @code
     * nlohmann::ordered_json oj { };
     * JsonUtil::to_json(oj, value);
     * @endcode
     */
    template <class T>
    static void to_json(nlohmann::ordered_json& j, const T& t);
};

template<class T>
T JsonUtil::from_json(const nlohmann::json& j) {
    T t { };
    t = j.get<T>();
    return t;
}

template<class T>
T JsonUtil::from_json(const nlohmann::ordered_json& j) {
    T t { };
    t = j.get<T>();
    return t;
}

template<class T>
void JsonUtil::to_json(nlohmann::json& j, const T& t) {
    j = t;
}

template<class T>
void JsonUtil::to_json(nlohmann::ordered_json& j, const T& t) {
    j = t;
}


#endif //RIKKI_PATCHER_UTILS_JSON_UTIL_HPP
