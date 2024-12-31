#ifndef RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_DIALOGUE_KEY_MGR_HPP
#define RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_DIALOGUE_KEY_MGR_HPP
#include "precompiled.hpp"

/* dialogue_key_mgr.hpp
 *  Included structs:
 *      - DialogueKeyMgr
 *      - ChoiceKeyMgr
 */

// ======================= S T R U C T =======================
// ===    DialogueKeyMgr
// ======================= S T R U C T =======================

struct DialogueKeyMgr {
    static constexpr int32_t ID_DIALOGUE               = 11;
    static constexpr int32_t IDX_SPEAKER                = 3;
    static constexpr int32_t IDX_DIALOGUE_SPAN = 6; // DialogueUtil::extract_texts_from_span

    static constexpr int32_t IDX_ATTS = 11;
    static constexpr      auto KEY_ATTS = "atts";
};

// ======================= S T R U C T =======================
// ===    ChoiceKeyMgr
// ======================= S T R U C T =======================

struct ChoiceKeyMgr {
    static constexpr int32_t ID_CHOICE   = 4;
    static constexpr int32_t IDX_CHOICE = 1;
};


#endif //RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_DIALOGUE_KEY_MGR_HPP
