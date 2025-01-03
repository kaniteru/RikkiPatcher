#ifndef RIKKI_PATCHER_RIKKI_DATA_UI_FONT_UI_FONT_JSON_HPP
#define RIKKI_PATCHER_RIKKI_DATA_UI_FONT_UI_FONT_JSON_HPP
#include "precompiled.hpp"
#include "utils/json_util.hpp"

// ======================= S T R U C T =======================
// ===    j::UIFont
// ======================= S T R U C T =======================

namespace j {
struct UIFont {
    std::string fonttype;
    std::string name;
    std::string path;
    int32_t size;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UIFont,
        fonttype,
        name,
        path,
        size);

    ORDERED_NLOHMANN_DEFINE_TYPE_INTRUSIVE(UIFont,
        fonttype,
        name,
        path,
        size);

    bool operator==(const UIFont&) const;
};
}


#endif //RIKKI_PATCHER_RIKKI_DATA_UI_FONT_UI_FONT_JSON_HPP
