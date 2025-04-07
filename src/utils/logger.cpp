#include "logger.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/dir_mgr_enum.hpp"

// ======================== C L A S S ========================
// ===    Logger
// ======================== C L A S S ========================

Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

Logger::Logger() :
    m_ofs(DirMgr::get(eDir::DIR_PROJ_LOG), std::ios::out | std::ios::trunc) {

    ktd::enable_virtual_terminal();
    m_pool.start();
}

Logger::~Logger() {
    while (!m_pool.is_empty()) { }
    m_pool.stop();

    if (m_ofs.is_open()) {
        m_ofs.close();
    }
}
