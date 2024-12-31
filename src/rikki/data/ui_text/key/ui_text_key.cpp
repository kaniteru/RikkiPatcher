#include "ui_text_key.hpp"

SettingUITextKey::SettingUITextKey(const char* a, const char* b, const char* c, const char* d) :
    m_iKey(a),
    m_iiKey(b),
    m_iiiKey(c),
    m_textKey(d) { }

DialogType1UITextKey::DialogType1UITextKey(const char* a, const char* b) :
    m_ikey(a),
    m_iiKey(b) { }

DialogType2UITextKey::DialogType2UITextKey(const char* a, const int32_t b, const uint32_t c, const uint32_t d) :
    m_ikey(a),
    m_iIdx(b),
    m_iiIdx(c),
    m_iiiIdx(d) { }

InGameUITextKey::InGameUITextKey(const char* a, const char* b, const uint32_t c, const uint32_t d, const char* e, const char* f) :
    m_iKey(a),
    m_iiKey(b),
    m_iIdx(c),
    m_iiIdx(d),
    m_iiiKey(e),
    m_iiiiKey(f) { }
