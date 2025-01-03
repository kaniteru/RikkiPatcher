#ifndef RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_PATCHER_HPP
#include "precompiled.hpp"
#include "rikki/patcher/i_patcher.hpp"

/* ui_patcher.hpp
 *  Included classes:
 *      - UIPatcher
 */

class UI;

// ======================== C L A S S ========================
// ===    UIPatcher
// ======================== C L A S S ========================

class UIPatcher final : public IPatcher {
public:
    PatcherResult patch() final;
    PatcherResult migration() final;
    PatcherResult generate_migration_info() final;

    bool close();
public:
    explicit UIPatcher(const path_t& src);
    ~UIPatcher() final;
private:
    std::unique_ptr<UI> m_pUI;
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_UI_PATCHER_HPP
