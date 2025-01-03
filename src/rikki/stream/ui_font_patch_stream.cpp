#include "ui_font_patch_stream.hpp"
#include "rikki/data/ui_font/ui_font_json.hpp"

// ======================== C L A S S ========================
// ===    UIFontPatchStream
// ======================== C L A S S ========================

font_vector_t UIFontPatchStream::get_fonts() {
    font_vector_t result { };

    for (const auto& it : m_j) {
        j::UIFont buf = it;
        result.emplace_back(std::move(buf));
    }

    return result;
}

size_t UIFontPatchStream::add_fonts(const font_vector_t& fonts) {
    size_t result = 0;

    for (const auto& it : fonts) {
        j::UIFont buf = it;

        // todo: check duplicate fonts
        /*for (const auto& [type, name, path, size] : this->get_fonts()) {
            if (name) {

            }
        }*/

        if (const auto vec = this->get_fonts(); std::ranges::find(vec, buf) != vec.end()) {
           continue;
        }

        m_j.emplace_back(std::move(buf));
        result++;
    }

    return result;
}

UIFontPatchStream::UIFontPatchStream(const path_t& file) :
    IRikkiStream(file) { }
