#ifndef RIKKI_PATCHER_RIKKI_EXTRACTOR_COPY_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_EXTRACTOR_COPY_EXTRACTOR_HPP
#include "precompiled.hpp"
#include "i_extractor.hpp"

/* copy_extractor.hpp
 *  Included classes:
 *      - CopyExtractor
 */

// ======================== C L A S S ========================
// ===    CopyExtractor
// ======================== C L A S S ========================

class CopyExtractor final : public IExtractor {
public:
    size_t extract() final;

public:
    explicit CopyExtractor(const path_t & dst);
private:
    const path_t m_db;
};


#endif //RIKKI_PATCHER_RIKKI_EXTRACTOR_COPY_EXTRACTOR_HPP
