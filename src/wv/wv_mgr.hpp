#ifndef RIKKI_PATCHER_WV_WV_MGR_HPP
#define RIKKI_PATCHER_WV_WV_MGR_HPP
#include "precompiled.hpp"

using wv_ptr_t = std::shared_ptr<webview::webview>;

/* wv_mgr.hpp
 *  Included classes:
 *      - WvMgr
 *
 *  Included structs:
 *      - WvMgr::impl
 */

// ======================== C L A S S ========================
// ===    WvMgr
// ======================== C L A S S ========================

class WvMgr final {
public:
    /**
     * @brief Initialize WvMgr.
     *
     * @param [in, optional] enableF12
     * @param [in, out, optional] hWnd
     */
    static void init(bool enableF12 = false, void* hWnd = nullptr);

    /**
     * @return Returns webview instance.
     */
    static wv_ptr_t get();

    WvMgr& operator=(const WvMgr&) = delete;
    WvMgr(const WvMgr&) = delete;
private:
    static WvMgr& instance();

    WvMgr();
    ~WvMgr();
private:
    struct impl;
    std::unique_ptr<impl> m_pImpl;
};


#endif //RIKKI_PATCHER_WV_WV_MGR_HPP
