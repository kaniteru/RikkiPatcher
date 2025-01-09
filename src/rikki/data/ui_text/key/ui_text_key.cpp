#include "ui_text_key.hpp"

// ======================= S T R U C T =======================
// ===    SettingUITextKey
// ======================= S T R U C T =======================

SettingUITextKey::SettingUITextKey(const char* a1, const char* a2, const char* a3, const char* a4) :
    m_iKey(a1),
    m_iiKey(a2),
    m_iiiKey(a3),
    m_textKey(a4) { }

// ======================= S T R U C T =======================
// ===    DialogType1UITextKey
// ======================= S T R U C T =======================

DialogType1UITextKey::DialogType1UITextKey(const char* a1, const char* a2) :
    m_ikey(a1),
    m_iiKey(a2) { }

// ======================= S T R U C T =======================
// ===    DialogType2UITextKey
// ======================= S T R U C T =======================

DialogType2UITextKey::DialogType2UITextKey(const char* a1, const int32_t a2, const uint32_t a3, const uint32_t a4) :
    m_ikey(a1),
    m_iIdx(a2),
    m_iiIdx(a3),
    m_iiiIdx(a4) { }

// ======================= S T R U C T =======================
// ===    InGameUITextKey
// ======================= S T R U C T =======================

InGameUITextKey::InGameUITextKey(const char* a1, const char* a2, const uint32_t a3, const uint32_t a4, const char* a5, const char* a6) :
    m_iKey(a1),
    m_iiKey(a2),
    m_iIdx(a3),
    m_iiIdx(a4),
    m_iiiKey(a5),
    m_iiiiKey(a6) { }

// ======================= S T R U C T =======================
// ===    TitleUITextKey
// ======================= S T R U C T =======================

TitleUITextKey::TitleUITextKey(const char* a1, const char* a2, const char* a3, uint32_t a4, const char* a5, uint32_t a6) :
    m_iKey(a1),
    m_iiKey(a2),
    m_iiiKey(a3),
    m_iIdx(a4),
    m_iiiiKey(a5),
    m_iiIdx(a6) { }
