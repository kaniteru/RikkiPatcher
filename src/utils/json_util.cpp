#include "json_util.hpp"

// ======================== C L A S S ========================
// ===    JsonUtil
// ======================== C L A S S ========================

bool JsonUtil::load_from_file(nlohmann::json& j, const path_t& file) {
    if (auto fs = std::fstream(file, std::ios::in); fs.is_open()) {
        fs >> j;
        fs.close();
        return true;
    }

    return false;
}

bool JsonUtil::load_from_file(nlohmann::ordered_json& j, const path_t& file) {
    if (auto fs = std::fstream(file, std::ios::in); fs.is_open()) {
        fs >> j;
        fs.close();
        return true;
    }

    return false;
}

bool JsonUtil::save_into_file(const nlohmann::json& j, const path_t& file) {
    if (auto fs = std::fstream(file, std::ios::out | std::ios::trunc); fs.is_open()) {
        fs << j.dump(4);
        fs.close();
        return true;
    }

    return false;
}

bool JsonUtil::save_into_file(const nlohmann::ordered_json& j, const path_t& file) {
    if (auto fs = std::fstream(file, std::ios::out | std::ios::trunc); fs.is_open()) {
        fs << j.dump(4);
        fs.close();
        return true;
    }

    return false;
}
