#include "i_patcher.hpp"
#include "rikki/data/data_path.hpp"

PatcherResult& PatcherResult::operator+=(const PatcherResult& rhs) {
    m_total   += rhs.m_total;
    m_ok       += rhs.m_ok;
    m_failed  += rhs.m_failed;
    m_passed += rhs.m_passed;
    return *this;
}

bool PatcherResult::operator==(const PatcherResult& rhs) const {
    return m_total == rhs.m_total && m_ok == rhs.m_ok && m_failed == rhs.m_failed && m_passed == rhs.m_passed;
}

bool IPatcher::is_available() const {
    return m_isAvailable;
}

IPatcher::IPatcher(const path_t& dir) :
    m_isAvailable(false),
    m_dir(dir),
    m_migrDir(path_t(dir) / MigrPath::BASE_FOLDER_NAME) { }
