#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_KEY_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_KEY_HPP
#include "precompiled.hpp"

/* ui_key.hpp
 *  Included structs:
 *      - IUIKey
 *      - SettingUITextKey
 *      - DialogType1UITextKey
 *      - DialogType2UITextKey
 *      - InGameUITextKey
 */

struct IUIKey { };

// ======================= S T R U C T =======================
// ===    SettingUITextKey
// ======================= S T R U C T =======================

struct SettingUITextKey : IUIKey {
    const char* m_iKey;
    const char* m_iiKey;
    const char* m_iiiKey; // id
    const char* m_textKey;

    SettingUITextKey(const char* a, const char* b, const char* c, const char* d);
};

// ======================= S T R U C T =======================
// ===    DialogUITextKey
// ======================= S T R U C T =======================

struct DialogType1UITextKey : IUIKey {
    const char* m_ikey;
    const char* m_iiKey;

    DialogType1UITextKey(const char* a, const char* b);
};

struct DialogType2UITextKey : IUIKey {
    const char* m_ikey;
    int32_t m_iIdx;
    uint32_t m_iiIdx;
    uint32_t m_iiiIdx;

    explicit DialogType2UITextKey(const char* a, int32_t b, uint32_t c, uint32_t d);
};

// ======================= S T R U C T =======================
// ===    InGameUITextKey
// ======================= S T R U C T =======================

struct InGameUITextKey : IUIKey {
    const char* m_iKey;
    const char* m_iiKey;
    uint32_t m_iIdx;
    uint32_t m_iiIdx;
    const char* m_iiiKey;
    const char* m_iiiiKey;

    InGameUITextKey(const char* a, const char* b, uint32_t c, uint32_t d, const char* e, const char* f);
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_KEY_HPP
