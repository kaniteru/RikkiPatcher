#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_TEXT_KEY_UI_TEXT_TITLE_KEY_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_TEXT_KEY_UI_TEXT_TITLE_KEY_HPP
#include "precompiled.hpp"
#include "ui_text_key.hpp"

/* ui_text_title_key.hpp
 *  Included classes:
 *      - TitleUITextKeyMgr
 */

// ======================= S T R U C T =======================
// ===    TitleUITextKeyMgr
// ======================= S T R U C T =======================

struct TitleUITextKeyMgr {
    static const TitleUITextKey unlocked_select_chapter_msgbox_title;
    static const TitleUITextKey unlocked_select_chapter_msgbox_line1;
    static const TitleUITextKey unlocked_select_chapter_msgbox_line2;

    static constexpr auto KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_TITLE = "title";
    static constexpr auto KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_LINE1 = "line_1";
    static constexpr auto KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_LINE2 = "line_2";

    static const std::map<const char*, const TitleUITextKey&> g_keys;
    static constexpr std::array<std::pair<const char*, const TitleUITextKey*>, 3> g_arr = {
        std::make_pair(KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_TITLE, &unlocked_select_chapter_msgbox_title),
        std::make_pair(KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_LINE1, &unlocked_select_chapter_msgbox_line1),
        std::make_pair(KEY_UNLOCKED_SELECT_CHAPTER_MSGBOX_LINE2, &unlocked_select_chapter_msgbox_line2)
    };
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_TEXT_KEY_UI_TEXT_TITLE_KEY_HPP
