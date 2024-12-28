#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_KEY_MGR_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_KEY_MGR_HPP
#include "precompiled.hpp"

/* ui_key_mgr.hpp
 *  Included classes:
 *      - UIKeyMgr
 */

// ======================= S T R U C T =======================
// ===    UIKeyMgr
// ======================= S T R U C T =======================

class UIKeyMgr {
public:
    template <typename T>
    T* get(const char* pKeyStr);
private:
    template <typename T>
    void add(const char* pKeyStr, const T* pKey);

    void add_ui_text_in_game();
    void add_ui_text_setting();
    void add_ui_text_dialog();

public:
    UIKeyMgr();
private:
    std::map<const char*, const void*> m_keys;
};

template<typename T>
T* UIKeyMgr::get(const char* pKeyStr) {
    if (const auto it = m_keys.find(pKeyStr); it != m_keys.end()) {
        return static_cast<T*>(it->second);
    }

    return nullptr;
}

template<typename T>
void UIKeyMgr::add(const char* pKeyStr, const T* const pKey) {
    m_keys[pKeyStr] = reinterpret_cast<const void*>(pKey);
}


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_KEY_UI_KEY_MGR_HPP
