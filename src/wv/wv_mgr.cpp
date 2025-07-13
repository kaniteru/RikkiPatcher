#include "wv_mgr.hpp"
#include "rikki/dir_mgr.hpp"

#include "utils/logger.hpp"

// ======================= S T R U C T =======================
// ===    WvMgr::impl
// ======================= S T R U C T =======================

struct WvMgr::impl {
    impl(bool enableF12, void* hWnd) {
        LOG(INFO, "Initializing webview");
        m_pWv = std::make_shared<webview::webview>(enableF12, hWnd);
    }

    ~impl() {
        LOG(VERBOSE, "Destroying webview");
    }

    std::shared_ptr<webview::webview> m_pWv;
};

// ======================== C L A S S ========================
// ===    WvMgr
// ======================== C L A S S ========================

void WvMgr::init(bool enableF12, void* hWnd) {
    DirMgr::init({ });
    LOG(INFO, "Initializing WvMgr");

    if (WvMgr::instance().m_pImpl) {
        LOG(FATAL, "WvMgr already initialized");
        throw std::runtime_error("WvMgr already initialized");
    }

    WvMgr::instance().m_pImpl = std::make_unique<impl>(enableF12, hWnd);
}

wv_ptr_t WvMgr::get() {
    return WvMgr::instance().m_pImpl->m_pWv;
}

WvMgr& WvMgr::instance() {
    static WvMgr instance;
    return instance;
}

WvMgr::WvMgr() { }

WvMgr::~WvMgr() { }
