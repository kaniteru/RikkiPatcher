#include "ui_font.hpp"
#include "ui_font_json.hpp"
#include "rikki/data/ui/ui.hpp"

// ======================== C L A S S ========================
// ===    UIFont
// ======================== C L A S S ========================

font_vector_t UIFont::get_fonts() const {
    font_vector_t result { };

    this->iterate_elements([&](const auto& elem) {
        j::UIFont buf { };
        buf = elem;
        result.emplace_back(std::move(buf));
    });

    return result;
}

void UIFont::set_fonts(const font_vector_t& fonts) const {
    auto& j = this->get_json_font_arr();
    j.clear();

    for (const auto& it : fonts) {
        j.emplace_back(it);
    }
}

bool UIFont::save() {
    throw std::exception("Not Implemented. Use UI::save().");
}

bool UIFont::save(const path_t& dir) {
    throw std::exception("Not Implemented. Use UI::save().");
}

void UIFont::iterate_elements(const font_iterator_t& callback) const {
    for (auto& elem : this->get_json_font_arr()) {
        callback(elem);
    }
}

nlohmann::json& UIFont::get_json_font_arr() const {
    return m_pUI->get_json()["asset/json/config.json"]["FONTS"];
}

UIFont::UIFont(std::shared_ptr<UI> ui) :
    m_pUI(ui) {

    m_isValid = true;
}
