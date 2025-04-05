#ifndef RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_TEXT_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_TEXT_PATCHER_HPP
#include "precompiled.hpp"
#include "rikki/patcher/i_patcher.hpp"

/* ui_text_patcher.hpp
 *  Included classes:
 *      - UITextPatcher
 *      - IUITextPatcher
 *      - InGameUITextPatcher
 *      - SettingUITextPatcher
 *      - DialogUITextPatcher
 *      - TitleUITextPatcher
 */

class UIText;

// ======================== C L A S S ========================
// ===    UITextPatcher
// ======================== C L A S S ========================

class UITextPatcher final : public IPatcher {
public:
    /**
     * @brief Do custom patch into game data.
     *
     * @return Returns patched data count.
     */
    PatcherResult patch() final;

    /**
     * @brief Migrate custom data using data data.
     *              Game data must be unmodified.
     *
     * @return Returns true if migrated successfully.
     */
    PatcherResult migration() final;

    PatcherResult extract() final;

public:
    /**
     * @brief Init using custom patch data directory.
     *
     * @param [in] src Root path of custom patch data directory.
     * @param [in] pUT ptr of UIText.
     */
    UITextPatcher(const path_t& src, std::shared_ptr<UIText> pUT);
private:
    std::shared_ptr<UIText> m_pUT; /* Ptr of UIText. */
};

// ======================== C L A S S ========================
// ===    IUITextPatcher
// ======================== C L A S S ========================

class IUITextPatcher : public IPatcher {
public:
    /**
     * @param [in] src Target root folder of custom patch data.
     * @param [in] ut  Ptr of loaded UIText.
     */
    IUITextPatcher(const path_t& src, std::shared_ptr<UIText> ut);
protected:
    std::shared_ptr<UIText> m_pUT; /* Reference of UIText */
};

// ======================== C L A S S ========================
// ===    InGameUITextPatcher
// ======================== C L A S S ========================

class InGameUITextPatcher final : public IUITextPatcher {
public:
    PatcherResult patch() final;

    PatcherResult migration() final;

    PatcherResult extract() final;

public:
    /**
     * @param [in] src Target root folder of custom patch data.
     * @param [in] ut  Ptr of loaded UIText.
     */
    InGameUITextPatcher(const path_t& src, std::shared_ptr<UIText> pUT);
private:
    const path_t m_db;         /* Path of in-game patch data folder */
    const path_t m_migrDB; /* Path of in-game migration data folder */
};

// ======================== C L A S S ========================
// ===    SettingUITextPatcher
// ======================== C L A S S ========================

class SettingUITextPatcher final : public IUITextPatcher {
public:
    PatcherResult patch() final;

    PatcherResult migration() final;

    PatcherResult extract() final;

public:
    /**
     * @param [in] src Target root folder of custom patch data.
     * @param [in] ut  Ptr of loaded UIText.
     */
    SettingUITextPatcher(const path_t& src, std::shared_ptr<UIText> pUT);
private:
    const path_t m_db;         /* Path of setting patch data folder */
    const path_t m_migrDB; /* Path of setting migration data folder */
};

// ======================== C L A S S ========================
// ===    DialogUITextPatcher
// ======================== C L A S S ========================

class DialogUITextPatcher final : public IUITextPatcher {
public:
    PatcherResult patch() final;

    PatcherResult migration() final;

    PatcherResult extract() final;

public:
    /**
     * @param [in] src Target root folder of custom patch data.
     * @param [in] ut  Ptr of loaded UIText.
     */
    DialogUITextPatcher(const path_t& src, std::shared_ptr<UIText> pUT);
private:
    const path_t m_db;         /* Path of dialog patch data folder */
    const path_t m_migrDB; /* Path of dialog migration data folder */
};

// ======================== C L A S S ========================
// ===    TitleUITextPatcher
// ======================== C L A S S ========================

class TitleUITextPatcher final : public IUITextPatcher {
public:
    PatcherResult patch() final;
    PatcherResult migration() final;
    PatcherResult extract() final;

public:
    /**
     * @param [in] src Target root folder of custom patch data.
     * @param [in] ut  Ptr of loaded UIText.
     */
    TitleUITextPatcher(const path_t& src, std::shared_ptr<UIText> pUT);
private:
    const path_t m_db;         /* Path of title patch data folder */
    const path_t m_migrDB; /* Path of title migration data folder */
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_UI_UI_TEXT_PATCHER_HPP
