#include "data_path.hpp"

// ======================= S T R U C T =======================
// ===    DialoguePath
// ======================= S T R U C T =======================

const path_t DialoguePath::PATCH_FOLDER_DIALOGUE = path_t(DialoguePath::DIALOGUE_FOLDER_NAME);
const path_t DialoguePath::PATCH_FOLDER_CHOICE = path_t(DialoguePath::CHOICE_FOLDER_NAME);
const path_t DialoguePath::MIGR_FOLDER_DIALOGUE = path_t(MigrPath::BASE_FOLDER_NAME).append(DialoguePath::DIALOGUE_FOLDER_NAME);
const path_t DialoguePath::MIGR_FOLDER_CHOICE = path_t(MigrPath::BASE_FOLDER_NAME).append(DialoguePath::CHOICE_FOLDER_NAME);

// ======================= S T R U C T =======================
// ===    UIPath
// ======================= S T R U C T =======================

const path_t UIPath::PATCH_BASE = path_t(UIPath::BASE_FOLDER_NAME);
const path_t UIPath::MIGR_BASE = path_t(MigrPath::BASE_FOLDER_NAME).append(UIPath::BASE_FOLDER_NAME);

// ======================= S T R U C T =======================
// ===    UITextPath
// ======================= S T R U C T =======================

const path_t UITextPath::PATCH_BASE = path_t(UIPath::PATCH_BASE).append(UITextPath::BASE_FOLDER_NAME);
const path_t UITextPath::MIGR_BASE = path_t(UIPath::MIGR_BASE).append(UITextPath::BASE_FOLDER_NAME);

const path_t UITextPath::PATCH_FILE_IN_GAME = path_t(UITextPath::PATCH_BASE) / UITextPath::IN_GAME_FILE_NAME;
const path_t UITextPath::PATCH_FILE_SETTING = path_t(UITextPath::PATCH_BASE) / UITextPath::SETTING_FILE_NAME;
const path_t UITextPath::PATCH_FILE_DIALOG = path_t(UITextPath::PATCH_BASE) / UITextPath::DIALOG_FILE_NAME;

const path_t UITextPath::MIGR_FILE_IN_GAME = path_t(UITextPath::MIGR_BASE) / UITextPath::IN_GAME_FILE_NAME;
const path_t UITextPath::MIGR_FILE_SETTING = path_t(UITextPath::MIGR_BASE) / UITextPath::SETTING_FILE_NAME;
const path_t UITextPath::MIGR_FILE_DIALOG = path_t(UITextPath::MIGR_BASE) / UITextPath::DIALOG_FILE_NAME;

// ======================= S T R U C T =======================
// ===    UIDialoguePath
// ======================= S T R U C T =======================

const path_t UIDialoguePath::PATCH_BASE = path_t(UIPath::PATCH_BASE).append(UIDialoguePath::BASE_FOLDER_NAME);
const path_t UIDialoguePath::MIGR_BASE = path_t(UIPath::MIGR_BASE).append(UIDialoguePath::BASE_FOLDER_NAME);

const path_t UIDialoguePath::PATCH_FOLDER_DIALOGUE = path_t(UIDialoguePath::PATCH_BASE).append(UIDialoguePath::DIALOGUE_FOLDER_NAME);
const path_t UIDialoguePath::PATCH_FOLDER_CHOICE = path_t(UIDialoguePath::PATCH_BASE).append(UIDialoguePath::CHOICE_FOLDER_NAME);

const path_t UIDialoguePath::MIGR_FOLDER_DIALOGUE = path_t(UIDialoguePath::MIGR_BASE).append(UIDialoguePath::DIALOGUE_FOLDER_NAME);
const path_t UIDialoguePath::MIGR_FOLDER_CHOICE = path_t(UIDialoguePath::MIGR_BASE).append(UIDialoguePath::CHOICE_FOLDER_NAME);

// ======================= S T R U C T =======================
// ===    UIFontPath
// ======================= S T R U C T =======================

const path_t UIFontPath::PATCH_BASE = path_t(UIPath::PATCH_BASE).append(UIFontPath::BASE_FOLDER_NAME);
const path_t UIFontPath::MIGR_BASE = path_t(UIPath::MIGR_BASE).append(UIFontPath::BASE_FOLDER_NAME);

const path_t UIFontPath::PATCH_FOLDER_FONTS_FILES = path_t(UIFontPath::PATCH_BASE).append(UIFontPath::FONTS_FILES_FOLDER_NAME);
const path_t UIFontPath::PATCH_FILE_FONTS_INFO = path_t(UIFontPath::PATCH_BASE).append(UIFontPath::FONTS_INFO_FILE_NAME);

const path_t UIFontPath::MIGR_FOLDER_FONTS_FILES = path_t(UIFontPath::MIGR_BASE).append(UIFontPath::FONTS_FILES_FOLDER_NAME);
const path_t UIFontPath::MIGR_FILE_FONTS_INFO = path_t(UIFontPath::MIGR_BASE).append(UIFontPath::FONTS_INFO_FILE_NAME);
