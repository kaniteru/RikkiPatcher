#include "ui_patch_stream.hpp"
#include "rikki/data/ui_text/ui_text_json.hpp"
#include "utils/json_util.hpp"

// ======================== C L A S S ========================
// ===    UITextPatchStream
// ======================== C L A S S ========================

template<class T>
T UITextPatchStream::get_texts() const {
    return JsonUtil::from_json<T>(m_j);
}

template j::InGameUIText UITextPatchStream::get_texts<j::InGameUIText>() const;
template j::SettingUIText UITextPatchStream::get_texts<j::SettingUIText>() const;
template j::DialogUIText UITextPatchStream::get_texts<j::DialogUIText>() const;
template j::TitleUIText UITextPatchStream::get_texts<j::TitleUIText>() const;

template<class T>
void UITextPatchStream::set_texts(const T& t) {
    JsonUtil::to_json(m_j, t);
}

template void UITextPatchStream::set_texts<j::InGameUIText>(const j::InGameUIText& t);
template void UITextPatchStream::set_texts<j::SettingUIText>(const j::SettingUIText& t);
template void UITextPatchStream::set_texts<j::DialogUIText>(const j::DialogUIText& t);
template void UITextPatchStream::set_texts<j::TitleUIText>(const j::TitleUIText& t);

void UITextPatchStream::clear() {
    m_j.clear();
}

bool UITextPatchStream::save() const {
    return JsonUtil::save_into_file(m_j, m_file);
}

UITextPatchStream::UITextPatchStream(const path_t& file) :
    m_file(file) {

    JsonUtil::load_from_file(m_j, m_file);
}
