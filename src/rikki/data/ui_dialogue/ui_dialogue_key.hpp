#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_DIALOGUE_UI_DIALOGUE_KEY_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_DIALOGUE_UI_DIALOGUE_KEY_HPP
#include "precompiled.hpp"

/* ui_dialogue_key.hpp
 *  Included structs:
 *      - UIDialogueKey
 */

// ======================= S T R U C T =======================
// ===    UIDialogueKey
// ======================= S T R U C T =======================

struct UIDialogueKey {
    static constexpr auto KEY_JSON1 = "asset/json/server/command/data/ws1.json";
    static constexpr auto KEY_JSON2 = "asset/json/server/command/data/ws2.json";
    static constexpr auto KEY_JSON3 = "asset/json/server/command/data/ws3.json";
    static constexpr auto KEY_JSON4 = "asset/json/server/command/data/ws4.json";

    static constexpr auto FILE_JSON1 = "ws1.json";
    static constexpr auto FILE_JSON2 = "ws2.json";
    static constexpr auto FILE_JSON3 = "ws3.json";
    static constexpr auto FILE_JSON4 = "ws4.json";

    /* key | json file name */
    static constexpr std::array<std::pair<const char*, const char*>, 4> g_arr {
        std::make_pair(KEY_JSON1, FILE_JSON1),
        std::make_pair(KEY_JSON2, FILE_JSON2),
        std::make_pair(KEY_JSON3, FILE_JSON3),
        std::make_pair(KEY_JSON4, FILE_JSON4)
    };
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_DIALOGUE_UI_DIALOGUE_KEY_HPP
