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

    explicit DialogType2UITextKey(const char* a);
};

// ======================= S T R U C T =======================
// ===    InGameUITextKey
// ======================= S T R U C T =======================

struct InGameUITextKey : IUIKey {
    const char* m_iKey;
    const char* m_iiKey;
    const char* m_iiiKey;
    const char* m_iiiiKey;

    InGameUITextKey(const char* a, const char* b, const char* c, const char* d);
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_KEY_HPP
