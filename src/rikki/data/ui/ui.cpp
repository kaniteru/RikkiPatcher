#include "ui.hpp"
#include "utils/json_util.hpp"

// ======================== C L A S S ========================
// ===    UI
// ======================== C L A S S ========================

bool UI::save() {
    return this->save(m_file);
}

bool UI::save(const path_t& dir) {
    return JsonUtil::save_into_file(m_j, dir);
}

nlohmann::json& UI::get_json() {
    return m_j;
}

UI::UI(const path_t& file) :
    m_file(file) {

    m_isValid = JsonUtil::load_from_file(m_j, file);
}
