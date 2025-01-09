#include "ui_text_title_key.hpp"

// ======================= S T R U C T =======================
// ===    TitleUITextKeyMgr
// ======================= S T R U C T =======================

const TitleUITextKey TitleUITextKeyMgr::unlocked_select_chapter_msgbox_title = {
    "asset/json/ui/data/ui19.json",
    "root",
    "children",
    1,
    "children",
    0
};

const TitleUITextKey TitleUITextKeyMgr::unlocked_select_chapter_msgbox_line1 = {
    "asset/json/ui/data/ui19.json",
    "root",
    "children",
    1,
    "children",
    1
};

const TitleUITextKey TitleUITextKeyMgr::unlocked_select_chapter_msgbox_line2 = {
    "asset/json/ui/data/ui19.json",
    "root",
    "children",
    1,
    "children",
    2
};

const std::map<const char*, const TitleUITextKey&> TitleUITextKeyMgr::g_keys = {
    { KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_TITLE, unlocked_select_chapter_msgbox_title },
    { KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_LINE1, unlocked_select_chapter_msgbox_line1 },
    { KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_LINE2, unlocked_select_chapter_msgbox_line2 }
};