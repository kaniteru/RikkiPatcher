#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_KEY_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_KEY_HPP
#include "precompiled.hpp"

struct SettingUITextKey {
    std::string m_iKey;
    std::string m_iiKey;
    std::string m_iiiKey;
};

struct DialogUITextKey {
    std::string m_ikey;
    std::string m_iiKey;
    std::string m_iiiKey; // ___cmdID
};

struct InGameUITextKey {
    std::string m_iKey;
    std::string m_iiKey;
    std::string m_iiiKey;
    std::string m_iiiiKey;
};


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_KEY_HPP
