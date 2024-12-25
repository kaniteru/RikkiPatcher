#include "i_patcher.hpp"

PatcherResult& PatcherResult::operator+=(const PatcherResult& rhs) {
    m_total   += rhs.m_total;
    m_ok       += rhs.m_ok;
    m_failed  += rhs.m_failed;
    m_passed += rhs.m_passed;
    return *this;
}

bool IPatcher::is_available() const {
    return m_isAvailable;
}

IPatcher::IPatcher(const path_t& dir) :
    m_isAvailable(false),
    m_dir(dir),
    m_migrDir(path_t(dir).append(FOLDER_MIGRATE)) { }
