#ifndef RIKKI_PATCHER_WV_WV_BINDER_HPP
#define RIKKI_PATCHER_WV_WV_BINDER_HPP
#include "precompiled.hpp"

/* wv_binder.hpp
 *  Included classes:
 *      - WvBinder
 */

// ======================== C L A S S ========================
// ===    WvBinder
// ======================== C L A S S ========================

class WvBinder {
public:
    void bind() const;

public:
    explicit constexpr WvBinder(webview::webview* wv) : m_wv(wv) {}
private:
    webview::webview* const m_wv;
};


#endif //RIKKI_PATCHER_WV_WV_BINDER_HPP
