#include "i_patcher.hpp"
#include "rikki/data/data_path.hpp"

// ======================= S T R U C T =======================
// ===    PatcherResult
// ======================= S T R U C T =======================

int32_t PatcherResult::total() const {
    return m_ok + m_failed + m_passed;
}

PatcherResult& PatcherResult::operator+=(const PatcherResult& rhs) {
    m_ok        += rhs.m_ok;
    m_failed  += rhs.m_failed;
    m_passed += rhs.m_passed;
    return *this;
}

bool PatcherResult::operator==(const PatcherResult& rhs) const {
    return m_ok == rhs.m_ok && m_failed == rhs.m_failed && m_passed == rhs.m_passed;
}

// ======================== C L A S S ========================
// ===    IPatcher
// ======================== C L A S S ========================

bool IPatcher::is_available() const {
    return m_isAvailable;
}

IPatcher::IPatcher(const path_t& dir) :
    m_isAvailable(false),
    m_dir(dir),
    m_migrDir(path_t(dir) / MigrPath::BASE_FOLDER_NAME) {

    fs::create_directories(m_dir);
    fs::create_directories(m_migrDir);
}
