#ifndef RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_UI_TEXT_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_UI_TEXT_EXTRACTOR_HPP
#include "precompiled.hpp"
#include "rikki/extractor/i_extractor.hpp"

/* ui_text_extractor.hpp
 *  Included classes:
 *      - UITextExtractor
 *      - IUITextExtractor
 *      - InGameUITextExtractor
 *      - SettingUITextExtractor
 *      - DialogUITextExtractor
 */

class UI;
class UIText;

// ======================== C L A S S ========================
// ===    UITextExtractor
// ======================== C L A S S ========================

class UITextExtractor : public IExtractor {
public:
    size_t extract() final;

public:
    /**
     * @param [in] dst Root path of custom patch data.
     * @param [in] pUI Ptr of loaded UI.
     */
    explicit UITextExtractor(const path_t& dst, UI* pUI);
private:
    UI* const m_pUI; /* Ptr of UI */
};

// ======================== C L A S S ========================
// ===    IUITextExtractor
// ======================== C L A S S ========================

class IUITextExtractor {
public:
    /**
     * @param [in] ut Ref of UIText.
     */
    explicit IUITextExtractor(UIText& ut);
protected:
    UIText& m_ut; /* Ref of UIText */
};

// ======================== C L A S S ========================
// ===    InGameUITextExtractor
// ======================== C L A S S ========================

class InGameUITextExtractor final : public IExtractor, IUITextExtractor {
public:
    size_t extract() final;

public:
    /**
     * @param [in] ut Ref of UIText. 
     * @param [in] dst Root path of custom patch data.
     */
    InGameUITextExtractor(UIText& ut, const path_t& dst);
private:
    const path_t m_db; /* Path of in-game patch file */
};

// ======================== C L A S S ========================
// ===    SettingUITextExtractor
// ======================== C L A S S ========================

class SettingUITextExtractor final : public IExtractor, IUITextExtractor {
public:
    size_t extract() final;

public:
    /**
     * @param [in] ut Ref of UIText. 
     * @param [in] dst Root path of custom patch data.
     */
    SettingUITextExtractor(UIText& ut, const path_t& dst);
private:
    const path_t m_db; /* Path of setting patch file */
};

// ======================== C L A S S ========================
// ===    DialogUITextExtractor
// ======================== C L A S S ========================

class DialogUITextExtractor final : public IExtractor, IUITextExtractor {
public:
    size_t extract() final;

public:
    /**
     * @param [in] ut Ref of UIText.
     * @param [in] dst Root path of custom patch data.
     */
    DialogUITextExtractor(UIText& ut, const path_t& dst);
private:
    const path_t m_db; /* Path of dialog data folder */
};


#endif //RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_UI_TEXT_EXTRACTOR_HPP
