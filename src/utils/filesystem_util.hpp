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
    /**
     * @brief List files in a directory and return them in natural-sorted order.
     *
     * @param dir Directory to enumerate.
     * @return Sorted list of paths from @p dir.
     */
    static std::vector<path_t> sort_files(const path_t& dir);

    /**
     * @brief Delete a directory tree (if it exists) and recreate it.
     *
     * @param dir Directory to reset.
     */
    static void delete_and_create_directories(const path_t& dir);

private:
    /**
     * @brief Extract numeric sequences from a filename (used for natural sorting).
     *
     * @param filename Filename (UTF-8).
     * @return Numbers found in left-to-right order.
     */
    static std::vector<int32_t> extract_nums(std::u8string_view filename);

    /**
     * @brief Comparator for natural ordering of paths by filename.
     *
     * @param a First path.
     * @param b Second path.
     * @return true if @p a should come before @p b.
     */
    static bool natural_sort_comparator(const path_t& a, const path_t& b);
};


#endif //RIKKI_PATCHER_UTILS_FILESYSTEM_UTIL_HPP