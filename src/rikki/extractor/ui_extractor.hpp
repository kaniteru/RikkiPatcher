#ifndef RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_EXTRACTOR_HPP
#include "precompiled.hpp"
#include "i_extractor.hpp"

/* ui_extractor.hpp
 *  Included classes:
 *      - UITextExtractor
 *      - IUITextExtractor
 *      - InGameUITextExtractor
 *      - SettingUITextExtractor
 *      - DialogUITextExtractor
 */

class UIText;

// ======================== C L A S S ========================
// ===    UITextExtractor
// ======================== C L A S S ========================

class UITextExtractor : public IExtractor {
public:
    size_t extract() final;

public:
    explicit UITextExtractor(const path_t& dst);
private:
    const path_t m_db;
};

// ======================== C L A S S ========================
// ===    IUITextExtractor
// ======================== C L A S S ========================

class IUITextExtractor {
public:
    explicit IUITextExtractor(UIText& ut);
protected:
    UIText& m_ut;
    constexpr static auto FOLDER_BASE = "ui/texts";
};

// ======================== C L A S S ========================
// ===    InGameUITextExtractor
// ======================== C L A S S ========================

class InGameUITextExtractor final : public IExtractor, IUITextExtractor {
public:
    size_t extract() final;

public:
    InGameUITextExtractor(UIText& ut, const path_t& dst);
private:
    path_t m_db;

    constexpr static auto FILE_NAME = "in_game.json";
};

// ======================== C L A S S ========================
// ===    SettingUITextExtractor
// ======================== C L A S S ========================

class SettingUITextExtractor final : public IExtractor, IUITextExtractor {
public:
    size_t extract() final;

public:
    SettingUITextExtractor(UIText& ut, const path_t& dst);
private:
    path_t m_db;

    constexpr static auto FILE_NAME = "setting.json";
};

// ======================== C L A S S ========================
// ===    DialogUITextExtractor
// ======================== C L A S S ========================

class DialogUITextExtractor final : public IExtractor, IUITextExtractor {
public:
    size_t extract() final;

public:
    DialogUITextExtractor(UIText& ut, const path_t& dst);
private:
    path_t m_db;

    constexpr static auto FILE_NAME = "dialog.json";
};


#endif //RIKKI_PATCHER_RIKKI_EXTRACTOR_UI_EXTRACTOR_HPP
