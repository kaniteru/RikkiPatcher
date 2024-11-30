#ifndef RIKKI_PATCHER_UTILS_JSON_UTIL_HPP
#define RIKKI_PATCHER_UTILS_JSON_UTIL_HPP
#include "precompiled.hpp"

class JsonUtil {
public:
    static bool load_from_file(nlohmann::json& j, const path_t& file);
    static bool save_into_file(const nlohmann::json& j, const path_t& file);
};


#endif //RIKKI_PATCHER_UTILS_JSON_UTIL_HPP
