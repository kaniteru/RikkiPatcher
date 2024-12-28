#ifndef RIKKI_PATCHER_UTILS_UI_TEXT_UTIL_HPP
#define RIKKI_PATCHER_UTILS_UI_TEXT_UTIL_HPP
#include "precompiled.hpp"

class UITextUtil {
public:
    static bool copy_startup_from_game_and_decrypt(path_t& file);
    static bool encrypt_startup_and_move_to_game();

    static constexpr auto FILE_NAME = "startup.json";
    static constexpr auto ZIP_FILE_NAME = "startup.zip";
    static constexpr auto TEMP_FOLDER_NAME = "uitext";
private:
    static constexpr auto PW = u8"gc_zip";
};


#endif //RIKKI_PATCHER_UTILS_UI_TEXT_UTIL_HPP
