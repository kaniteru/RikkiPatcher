#include "ui_migr_stream.hpp"
#include "rikki/data/ui_text/ui_text.hpp"
#include "../extractor/ui/ui_extractor.hpp"

#include "utils/json_util.hpp"

// ======================== C L A S S ========================
// ===    UITextMigrStream
// ======================== C L A S S ========================

template<class T>
T UITextMigrStream::get_texts() const {
    return JsonUtil::from_json<T>(m_j);
}

template InGameUIText UITextMigrStream::get_texts() const;
template SettingUIText UITextMigrStream::get_texts() const;
template DialogUIText UITextMigrStream::get_texts() const;

void UITextMigrStream::save_migration_data(const path_t& dir) {
    //todo: implement
}

UITextMigrStream::UITextMigrStream(const path_t& file) :
    IRikkiStream(file) { }
