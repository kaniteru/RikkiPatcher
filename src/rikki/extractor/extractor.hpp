#ifndef RIKKI_PATCHER_RIKKI_EXTRACTOR_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_EXTRACTOR_EXTRACTOR_HPP
#include "precompiled.hpp"

/* extractor.hpp
 *  Included classes:
 *      - Extractor
 */

// ======================== C L A S S ========================
// ===    Extractor
// ======================== C L A S S ========================

class Extractor {
public:
    static void do_extract(const path_t& dst);
    static void do_generate_migration_info(const path_t& dst);
};


#endif //RIKKI_PATCHER_RIKKI_EXTRACTOR_EXTRACTOR_HPP
