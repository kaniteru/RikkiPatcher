#ifndef RIKKI_PATCHER_UTILS_HASH_UTIL_HPP
#define RIKKI_PATCHER_UTILS_HASH_UTIL_HPP
#include "precompiled.hpp"

class HashUtil {
public:
    static std::string file_to_hash(const path_t& file);
    static std::string str_to_hash(std::string_view str);
};


#endif //RIKKI_PATCHER_UTILS_HASH_UTIL_HPP
