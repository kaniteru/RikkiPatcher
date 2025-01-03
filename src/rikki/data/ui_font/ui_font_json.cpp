#include "ui_font_json.hpp"

// ======================= S T R U C T =======================
// ===    j::UIFont
// ======================= S T R U C T =======================

bool j::UIFont::operator==(const UIFont& rhs) const {
    return fonttype == rhs.fonttype && name == rhs.name && path == rhs.path && size == rhs.size;
}
