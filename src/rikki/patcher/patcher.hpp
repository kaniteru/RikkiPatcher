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
    void do_patch() const;

    void do_migration() const;

    void do_extract() const;
public:
    /**
     * @param [in] dir Root path of custom patch data.
     */
    explicit Patcher(const path_t& dir);
    ~Patcher();
private:
    const path_t m_dir;
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_PATCHER_HPP
