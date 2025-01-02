#ifndef RIKKI_PATCHER_RIKKI_PATCHER_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_PATCHER_HPP
#include "precompiled.hpp"

/* patcher.hpp
 *  Included classes:
 *      - Patcher
 */

// ======================== C L A S S ========================
// ===    Patcher
// ======================== C L A S S ========================

class Patcher {
public:
    static void do_patch(const path_t& src);
    static void do_migration(const path_t& dir);
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_PATCHER_HPP
