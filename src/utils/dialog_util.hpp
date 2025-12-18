#ifndef RIKKI_PATCHER_UTILS_DIALOG_UTIL_HPP
#define RIKKI_PATCHER_UTILS_DIALOG_UTIL_HPP
#include "precompiled.hpp"

/* dialog_util.hpp
 *  Included classes:
 *      - DialogUtil
 */

// ======================== C L A S S ========================
// ===    DialogUtil
// ======================== C L A S S ========================

class DialogUtil {
public:
    /**
     * @brief Show a native folder picker dialog and store the selected directory.
     *
     * @param[out] dir Receives the chosen directory when the user accepts.
     * @return true if a folder was selected, false if canceled or on error.
     *
     * @code
     * path_t dir { ... };
     * if (DialogUtil::folder_select_dialog(dir)) {
     *     // use dir
     * } else {
     *     // dialog was canceled
     * }
     * @endcode
     */
    static bool folder_select_dialog(path_t& dir);
};


#endif //RIKKI_PATCHER_UTILS_DIALOG_UTIL_HPP
