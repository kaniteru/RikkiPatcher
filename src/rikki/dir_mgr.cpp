#include "dir_mgr.hpp"
#include "dir_mgr_enum.hpp"

// ======================= S T R U C T =======================
// ===    DirMgr::impl
// ======================= S T R U C T =======================

class DirMgr::impl {
public:
    void init(const path_t& gmDir);
    const path_t& get(eDir type);

public:
    ~impl();
private:
    std::shared_mutex m_mtx;
    std::unordered_map<eDir, path_t> m_dirs;
};

void DirMgr::impl::init(const path_t& gmDir) {
    std::lock_guard lock(m_mtx);
    m_dirs.clear();

    auto add = [this](const eDir e, const fs::path& d) {
        m_dirs[e] = d;
    };

    auto add_dir = [this](const eDir e, const eDir parent, const char* s) {
        const auto dir = path_t(m_dirs[parent]).append(s);
        fs::create_directories(dir);
        m_dirs[e] = dir;
    };

    add(DIR_PROJ_BASE, fs::current_path());
    add_dir(DIR_PROJ_TEMP, DIR_PROJ_BASE, "temp");

    add(DIR_PROJ_LANG, fs::current_path().append("lang"));
    add(DIR_PROJ_CONFIG, fs::current_path().append("config.json"));
    add(DIR_PROJ_LOG, fs::current_path().append("log.txt"));

    add_dir(DIR_PROJ_DATA_EXTRACED, DIR_PROJ_BASE, "extracted");

    add(DIR_PROJ_EXE_7ZIP, fs::current_path().append("7zip").append("7za.exe"));

    add(DIR_GAME_BASE, gmDir);
    // todo: improve
    add(DIR_GAME_FONTS, path_t(gmDir).append("asset").append("font"));
    const auto json = path_t(gmDir).append("asset").append("json");
    add(DIR_GAME_JSON_STARTUP, path_t(json).append("startup.json"));
    add(DIR_GAME_JSON_DIALOGUES, path_t(json).append("server").append("scene"));
}

const path_t& DirMgr::impl::get(const eDir type) {
    std::shared_lock lock(m_mtx);
    return m_dirs.at(type);
}

DirMgr::impl::~impl() {
    fs::remove_all(this->get(DIR_PROJ_TEMP));
}

// ======================== C L A S S ========================
// ===    DirMgr
// ======================== C L A S S ========================

void DirMgr::init(const path_t& gmDir) {
    DirMgr::instance().m_pImpl->init(gmDir);
}

const path_t& DirMgr::get(const eDir type) {
    return DirMgr::instance().m_pImpl->get(type);
}

DirMgr& DirMgr::instance() {
    static DirMgr mgr;
    return mgr;
}

DirMgr::DirMgr() :
    m_pImpl(std::make_unique<DirMgr::impl>()) { }

DirMgr::~DirMgr() { }
