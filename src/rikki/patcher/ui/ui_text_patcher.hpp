#ifndef RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_TEXT_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_TEXT_PATCHER_HPP
#include "precompiled.hpp"
#include "rikki/patcher/i_patcher.hpp"

/* ui_text_patcher.hpp
 *  Included classes:
 *      - IUITextPatcher
 *      - InGameUITextPatcher
 *      - SettingUITextPatcher
 *      - DialogUITextPatcher
 *
 *   Note: Make child patcher private since it's only used in UIPatcher
 */

class UITextPatcher;
class UIText;

// ======================== C L A S S ========================
// ===    IUITextPatcher
// ======================== C L A S S ========================

class IUITextPatcher : protected IPatcher {
public:
    IUITextPatcher(UIText* ut, const path_t& src);
protected:
    UIText* const m_ut;         /* Reference of UIText */
    const path_t m_base;        /* Path of ui-texts custom patch dir */
    const path_t m_baseMigr; /* Path of ui-texts custom patch migration dir */
};

// ======================== C L A S S ========================
// ===    InGameUITextPatcher
// ======================== C L A S S ========================

class InGameUITextPatcher final : IUITextPatcher {
    PatcherResult patch() final;

    PatcherResult migration() final;

    PatcherResult generate_migration_info() final;

private:
    InGameUITextPatcher(UIText* ut, const path_t& src);

    friend UITextPatcher;
};

// ======================== C L A S S ========================
// ===    SettingUITextPatcher
// ======================== C L A S S ========================

class SettingUITextPatcher final : IUITextPatcher {
    PatcherResult patch() final;

    PatcherResult migration() final;

    PatcherResult generate_migration_info() final;

private:
    SettingUITextPatcher(UIText* ut, const path_t& src);

    friend UITextPatcher;
};

// ======================== C L A S S ========================
// ===    DialogUITextPatcher
// ======================== C L A S S ========================

class DialogUITextPatcher final : IUITextPatcher {
    PatcherResult patch() final;

    PatcherResult migration() final;

    PatcherResult generate_migration_info() final;

private:
    DialogUITextPatcher(UIText* ut, const path_t& src);

    friend UITextPatcher;
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_TEXT_PATCHER_HPP
