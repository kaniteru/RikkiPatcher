#include "ui_dialogue.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/dialogue/dialogue_json.hpp"

#include "utils/json_util.hpp"

// ======================== C L A S S ========================
// ===    UIDialogue
// ======================== C L A S S ========================

bool UIDialogue::save() {
    throw std::exception("Not Implemented. Use UI::save().");
}

bool UIDialogue::save(const path_t& path) {
    throw std::exception("Not Implemented. Use UI::save().");
}

void UIDialogue::iterate_elements(const dialogue_iterate_t& callback) {
    constexpr static auto KEY_ELEMETNS = "commands";
    constexpr static auto IDX_ID                = 0;

    for (auto& elem : m_pUI->get_json()[m_pKey][KEY_ELEMETNS]) {
        if (elem.empty() || !elem.is_array()) {
            continue;
        }

        if (auto& id = elem[IDX_ID]; id.is_number_integer()) {
            callback(id, elem);
        }
    }
}

UIDialogue::UIDialogue(const std::shared_ptr<UI> pUI, const char* const pKey) :
    m_pUI(pUI),
    m_pKey(pKey) {

    m_isValid = pUI->is_valid();
}
