#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_TEXT_KEY_UI_KEY_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_TEXT_KEY_UI_KEY_HPP
#include "precompiled.hpp"

/* ui_text_key.hpp
 *  Included structs:
 *      - IUIKey
 *      - SettingUITextKey
 *      - DialogType1UITextKey
 *      - DialogType2UITextKey
 *      - InGameUITextKey
 *      - TitleUITextKey
 */

// ======================= S T R U C T =======================
// ===    IUIKey
// ======================= S T R U C T =======================

struct IUIKey { };

// ======================= S T R U C T =======================
// ===    SettingUITextKey
// ======================= S T R U C T =======================

struct SettingUITextKey : IUIKey {
    const char* m_iKey;
    const char* m_iiKey;
    const char* m_iiiKey; // id
    const char* m_textKey;

    SettingUITextKey(const char* a1, const char* a2, const char* a3, const char* a4);
};

// ======================= S T R U C T =======================
// ===    DialogType1UITextKey
// ======================= S T R U C T =======================

struct DialogType1UITextKey : IUIKey {
    const char* m_ikey;
    const char* m_iiKey;

    DialogType1UITextKey(const char* a1, const char* a2);
};

// ======================= S T R U C T =======================
// ===    DialogType2UITextKey
// ======================= S T R U C T =======================

struct DialogType2UITextKey : IUIKey {
    const char* m_ikey;
    int32_t m_iIdx;
    uint32_t m_iiIdx;
    uint32_t m_iiiIdx;

    explicit DialogType2UITextKey(const char* a1, int32_t a2, uint32_t a3, uint32_t a4);
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

    InGameUITextKey(const char* a1, const char* a2, uint32_t a3, uint32_t a4, const char* a5, const char* a6);
};

// ======================= S T R U C T =======================
// ===    TitleUITextKey
// ======================= S T R U C T =======================

struct TitleUITextKey : IUIKey {
    const char* m_iKey;
    const char* m_iiKey;
    const char* m_iiiKey;
    uint32_t m_iIdx;
    const char* m_iiiiKey;
    uint32_t m_iiIdx;

    TitleUITextKey(const char* a1, const char* a2, const char* a3, uint32_t a4, const char* a5, uint32_t a6);
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_TEXT_KEY_UI_KEY_HPP
