#include "config.hpp"
#include "utils/json_util.hpp"

bool Config::exists(const char* key) {
    return m_j.contains(key);
}

bool Config::save() const {
    return JsonUtil::save_into_file(m_j, m_file);
}

Config::Config(const path_t& file) :
    m_file(file) {

    JsonUtil::load_from_file(m_j, m_file);
}
