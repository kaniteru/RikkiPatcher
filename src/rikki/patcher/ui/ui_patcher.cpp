#include "ui_patcher.hpp"
#include "rikki/data/ui/ui.hpp"
#include "rikki/data/ui_text/ui_text.hpp"
#include "ui_text_patcher.hpp"
#include "ui_font_patcher.hpp"
#include "ui_dialogue_patcher.hpp"

#include "utils/ui_text_util.hpp"

#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    UIPatcher
// ======================== C L A S S ========================

PatcherResult UIPatcher::patch() { // todo: check file exists
    if (!this->is_ready()) {
        return { };
    }

    PatcherResult result { };

    {
        auto pUT = std::make_shared<UIText>(m_pUI);

        UITextPatcher patcher(m_dir, pUT);
        result += patcher.patch();
    }

    {
        UIDialoguePatcher diaPatcher(m_dir, m_pUI);
        result += diaPatcher.patch();

        UIChoicePatcher choPatcher(m_dir, m_pUI);
        result += choPatcher.patch();
    }

    {
        UIFontPatcher patcher(m_dir, m_pUI);
        result += patcher.patch();
    }

    return result;
}

PatcherResult UIPatcher::migration() {
    if (!this->is_ready()) {
        return { };
    }

    PatcherResult result { };

    {
        auto pUT = std::make_shared<UIText>(m_pUI);

        UITextPatcher patcher(m_dir, pUT);
        result += patcher.migration();
    }

    {
        UIDialoguePatcher diaPatcher(m_dir, m_pUI);
        result += diaPatcher.migration();

        UIChoicePatcher choPatcher(m_dir, m_pUI);
        result += choPatcher.migration();
    }

    {
        UIFontPatcher patcher(m_dir, m_pUI);
        result += patcher.migration();
    }

    return result;
}

PatcherResult UIPatcher::extract() {
    if (!this->is_ready()) {
        return { };
    }

    PatcherResult result { };

    {
        auto pUT = std::make_shared<UIText>(m_pUI);

        UITextPatcher patcher(m_dir, pUT);
        result += patcher.extract();
        patcher.migration();
    }

    {
        UIDialoguePatcher diaPatcher(m_dir, m_pUI);
        result += diaPatcher.extract();

        UIChoicePatcher choPatcher(m_dir, m_pUI);
        result += choPatcher.extract();
    }

    {
        UIFontPatcher patcher(m_dir, m_pUI);
        result += patcher.extract();
    }

    return result;
}

bool UIPatcher::close() {
    if (!m_pUI) {
        return false;
    }

    if (!m_isAvailable) {
        m_pUI.reset();
        return false;
    }

    if (!m_pUI->save()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::PATCH_UI_FAILED_WRITE);
        m_pUI.reset();
        return false;
    }

    if (!UITextUtil::encrypt_startup_and_move_to_game()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::PATCH_UI_FAILED_COPY_TO_GAME);
    }

    m_pUI.reset();
    return true;
}

bool UIPatcher::is_ready() const {
    if (!m_isAvailable) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::PATCH_UI_FAILED_COPY);
        return false;
    }

    if (!m_pUI->is_valid()) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::PATCH_UI_FAILED_READ);
        return false;
    }

    return true;
}

UIPatcher::UIPatcher(const path_t& src) :
    IPatcher(src) {

    if (path_t file { }; UITextUtil::copy_startup_from_game_and_decrypt(file)) {
        m_isAvailable = true;
        m_pUI = std::make_unique<UI>(file);
    }
}

UIPatcher::~UIPatcher() {
    this->close();
}
