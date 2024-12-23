#include "ui_key.hpp"

SettingUITextKey::SettingUITextKey(const char* a, const char* b, const char* c, const char* d) :
    m_iKey(a),
    m_iiKey(b),
    m_iiiKey(c),
    m_textKey(d) { }

DialogType1UITextKey::DialogType1UITextKey(const char* a, const char* b) :
    m_ikey(a),
    m_iiKey(b) { }

DialogType2UITextKey::DialogType2UITextKey(const char* a) :
    m_ikey(a) { }

InGameUITextKey::InGameUITextKey(const char* a, const char* b, const char* c, const char* d) :
    m_iKey(a),
    m_iiKey(b),
    m_iiiKey(c),
    m_iiiiKey(d) { }
