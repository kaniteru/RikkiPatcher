#include "patcher.hpp"
#include "rikki/patcher/dialogue/dialogue_patcher.hpp"
#include "ui/ui_patcher.hpp"
#include "rikki/patcher/copy/copy_patcher.hpp"

#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    Patcher
// ======================== C L A S S ========================

void Patcher::do_patch() const {
    // apply dialogues
    DialoguePatcher diaPatcher(m_dir);
    diaPatcher.patch();

    // apply choices
    ChoicePatcher choPatcher(m_dir);
    choPatcher.patch();

    // apply ui-texts
    UIPatcher uiPatcher(m_dir);
    uiPatcher.patch();
    uiPatcher.close();

    // apply copy patches
    CopyPatcher cpyPatcher(m_dir);
    cpyPatcher.patch();
}

void Patcher::do_migration() const {
    // migrate dialogues data
    DialoguePatcher diaPatcher(m_dir);
    diaPatcher.migration();

    // migrate choices data
    ChoicePatcher choPatcher(m_dir);
    choPatcher.migration();

    // migrate ui data
    UIPatcher uiPatcher(m_dir);
    uiPatcher.migration();
    uiPatcher.close();

    // copy patcher doesn't support the migrating.
}

void Patcher::do_extract() const {
    fs::remove_all(m_dir);
    fs::create_directories(m_dir);

    // extract dialogues
    DialoguePatcher diaPatcher(m_dir);
    diaPatcher.extract();

    // extract choices
    ChoicePatcher choPatcher(m_dir);
    choPatcher.extract();

    // extract ui-texts
    UIPatcher uiPatcher(m_dir);
    uiPatcher.extract();
    uiPatcher.close();

    // extract copy patches
    CopyPatcher cpyPatcher(m_dir);
    cpyPatcher.extract();
}

Patcher::Patcher(const path_t& dir) :
    m_dir(dir) { }

Patcher::~Patcher() { }
