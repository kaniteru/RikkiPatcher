#ifndef RIKKI_PATCHER_UTILS_FILESYSTEM_UTIL_HPP
#define RIKKI_PATCHER_UTILS_FILESYSTEM_UTIL_HPP
#include "precompiled.hpp"

/* filesystem_util.hpp
 *  Included classes:
 *      - FilesystemUtil
 */

// ======================== C L A S S ========================
// ===    FilesystemUtil
// ======================== C L A S S ========================

class FilesystemUtil {
public:
    static std::vector<path_t> sort_files(const path_t& dir);
    static void delete_and_create_directories(const path_t& dir);

private:
    static std::vector<int32_t> extract_nums(std::u8string_view filename);
    static bool natural_sort_comparator(const path_t& a, const path_t& b);
};


#endif //RIKKI_PATCHER_UTILS_FILESYSTEM_UTIL_HPP
