#include "dialogue.hpp"
#include "dialogue_json.hpp"
#include "dialogue_key.hpp"

#include "utils/json_util.hpp"
#include "utils/dialogue_util.hpp"

// ======================== C L A S S ========================
// ===    Dialogue
// ======================== C L A S S ========================

bool Dialogue::save() {
    return this->save(m_file);
}

bool Dialogue::save(const path_t& path) {
    return JsonUtil::save_into_file(m_j, path);
}

void Dialogue::iterate_elements(const dialogue_iterate_t& callback) {
    constexpr static auto KEY_ELEMETNS = "customCommands";
    constexpr static auto IDX_ID                = 0;

    for (auto& elements : m_j[KEY_ELEMETNS]) {
        for (auto& elem : elements) {
            if (elem.empty() || !elem.is_array()) {
                continue;
            }

            if (auto& id = elem[IDX_ID]; id.is_number_integer()) {
                callback(id, elem);
            }
        }
    }
}

Dialogue::Dialogue(const path_t& file) :
    m_file(file) {

    m_isValid = JsonUtil::load_from_file(m_j, m_file);
}
