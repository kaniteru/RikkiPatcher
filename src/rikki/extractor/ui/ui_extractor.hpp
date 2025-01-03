#ifndef RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_EXTRACTOR_HPP
#include "precompiled.hpp"
#include "rikki/extractor/i_extractor.hpp"

/* ui_extractor.hpp
 *  Included classes:
 *      - UIExtractor
 */

// ======================== C L A S S ========================
// ===    UIExtractor
// ======================== C L A S S ========================

class UIExtractor final : public IExtractor {
public:
    size_t extract() final;

public:
    explicit UIExtractor(const path_t& dst);
};


#endif //RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_EXTRACTOR_HPP
