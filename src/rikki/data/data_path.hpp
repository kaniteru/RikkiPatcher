#ifndef RIKKI_PATCHER_RIKKI_DATA_DATA_PATH_HPP
#define RIKKI_PATCHER_RIKKI_DATA_DATA_PATH_HPP
#include "precompiled.hpp"

/* data_path.hpp
 *  Included structs:
 *      - MigrPath
 *      - DialoguePath
 *      - UIPath
 *      - UITextPath
 *      - UIDialoguePath
 *      - CopyPath
 */

// ======================= S T R U C T =======================
// ===    MigrPath
// ======================= S T R U C T =======================

struct MigrPath {
    static constexpr auto BASE_FOLDER_NAME = u8"migration";
};

// ======================= S T R U C T =======================
// ===    DialoguePath
// ======================= S T R U C T =======================

struct DialoguePath {
    static const path_t PATCH_FOLDER_DIALOGUE;
    static const path_t PATCH_FOLDER_CHOICE;

    static const path_t MIGR_FOLDER_DIALOGUE;
    static const path_t MIGR_FOLDER_CHOICE;

private:
    static constexpr auto BASE_FOLDER_NAME = u8"dialogue";

    static constexpr auto DIALOGUE_FOLDER_NAME = u8"dialogues";
    static constexpr auto CHOICE_FOLDER_NAME = u8"choices";
};

// ======================= S T R U C T =======================
// ===    UIPath
// ======================= S T R U C T =======================

struct UIPath {
    static const path_t PATCH_BASE;
    static const path_t MIGR_BASE;

private:
    static constexpr auto BASE_FOLDER_NAME = u8"ui";
};

// ======================= S T R U C T =======================
// ===    UITextPath
// ======================= S T R U C T =======================

struct UITextPath {
    static const path_t PATCH_BASE;
    static const path_t MIGR_BASE;

    static const path_t PATCH_FILE_IN_GAME;
    static const path_t PATCH_FILE_SETTING;
    static const path_t PATCH_FILE_DIALOG;
    static const path_t PATCH_FILE_TITLE;

    static const path_t MIGR_FILE_IN_GAME;
    static const path_t MIGR_FILE_SETTING;
    static const path_t MIGR_FILE_DIALOG;
    static const path_t MIGR_FILE_TITLE;

private:
    static constexpr auto BASE_FOLDER_NAME = u8"text";

    constexpr static auto IN_GAME_FILE_NAME = u8"in_game.json";
    constexpr static auto SETTING_FILE_NAME = u8"setting.json";
    constexpr static auto DIALOG_FILE_NAME = u8"dialog.json";
    constexpr static auto TITLE_FILE_NAME = u8"title.json";
};

// ======================= S T R U C T =======================
// ===    UIDialoguePath
// ======================= S T R U C T =======================

struct UIDialoguePath {
    static const path_t PATCH_BASE;
    static const path_t MIGR_BASE;

    static const path_t PATCH_FOLDER_DIALOGUE;
    static const path_t PATCH_FOLDER_CHOICE;

    static const path_t MIGR_FOLDER_DIALOGUE;
    static const path_t MIGR_FOLDER_CHOICE;

private:
    static constexpr auto BASE_FOLDER_NAME = u8"dialogue";

    static constexpr auto DIALOGUE_FOLDER_NAME = u8"dialogues";
    static constexpr auto CHOICE_FOLDER_NAME = u8"choices";
};

// ======================= S T R U C T =======================
// ===    UIFontPath
// ======================= S T R U C T =======================

struct UIFontPath {
    static const path_t PATCH_BASE;
    static const path_t MIGR_BASE;

    static const path_t PATCH_FOLDER_FONTS_FILES;
    static const path_t PATCH_FILE_FONTS_INFO;

    static const path_t MIGR_FOLDER_FONTS_FILES;
    static const path_t MIGR_FILE_FONTS_INFO;

private:
    static constexpr auto BASE_FOLDER_NAME = u8"font";

    static constexpr auto FONTS_FILES_FOLDER_NAME = u8"fonts";
    static constexpr auto FONTS_INFO_FILE_NAME = u8"fonts.json";
};

// ======================= S T R U C T =======================
// ===    CopyPath
// ======================= S T R U C T =======================

struct CopyPath {
    static const path_t PATCH_BASE;

    static const path_t PATCH_CONFIG_FILE;

    static constexpr auto CONFIG_FILE_NAME = u8"copy.json";
private:
    static constexpr auto BASE_FOLDER_NAME = u8"copy";
};


#endif //RIKKI_PATCHER_RIKKI_DATA_DATA_PATH_HPP
