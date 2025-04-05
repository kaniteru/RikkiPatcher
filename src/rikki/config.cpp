#include "config.hpp"
#include "dir_mgr.hpp"
#include "dir_mgr_enum.hpp"

#include "utils/json_util.hpp"

// ======================== C L A S S ========================
// ===    Config
// ======================== C L A S S ========================

bool Config::exists(const char* key) {
    std::shared_lock lock(Config::instance().m_mtx);
    return Config::instance().m_j.contains(key);
}

bool Config::save() {
    std::unique_lock lock(Config::instance().m_mtx);
    return JsonUtil::save_into_file(Config::instance().m_j, DirMgr::get(DIR_PROJ_CONFIG));
}

Config& Config::instance() {
    static Config instance;
    return instance;
}

Config::Config() {
    JsonUtil::load_from_file(m_j, DirMgr::get(DIR_PROJ_CONFIG));
}

Config::~Config() {
    this->save();
}
