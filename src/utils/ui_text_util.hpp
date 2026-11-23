#ifndef RIKKI_PATCHER_UTILS_UI_TEXT_UTIL_HPP
#define RIKKI_PATCHER_UTILS_UI_TEXT_UTIL_HPP
#include "precompiled.hpp"

// ======================== C L A S S ========================
// ===    UITextUtil
// ======================== C L A S S ========================

class UITextUtil {
public:
    /**
     * @brief Copy the game's UI startup archive into a temp folder and decrypt/unpack it.
     * Writes the full path of the decrypted/unpacked startup JSON into @p a file.
     *
     * @param[out] file Path to the decrypted/unpacked startup.json in the temp folder.
     * @return true on success, false on failure (errors are logged).
     */
    static bool copy_startup_from_game_and_decrypt(path_t& file);

    /**
     * @brief Encrypt/pack the patched startup JSON from the temp folder and move it back to the game.
     * Expects the temp folder and required files to exist (created by the decrypt step).
     *
     * @return true on success, false on failure (errors are logged).
     */
    static bool encrypt_startup_and_move_to_game();
};


#endif //RIKKI_PATCHER_UTILS_UI_TEXT_UTIL_HPP
