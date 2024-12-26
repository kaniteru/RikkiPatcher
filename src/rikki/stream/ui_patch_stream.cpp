#include "ui_patch_stream.hpp"
#include "rikki/data/ui/ui_json.hpp"

#include "utils/json_util.hpp"

void UITextPatchStream::clear() {
    m_j.clear();
}

bool UITextPatchStream::save() const {
    return JsonUtil::save_into_file(m_j, m_file);
}

UITextPatchStream::UITextPatchStream(const path_t& file) :
    m_file(file) { }

template<class T>
T UITextPatchStream::get_texts() const {
    return JsonUtil::from_json<T>(m_j);
}

template InGameUIText UITextPatchStream::get_texts<InGameUIText>() const;
template SettingUIText UITextPatchStream::get_texts<SettingUIText>() const;
template DialogUIText UITextPatchStream::get_texts<DialogUIText>() const;

template<class T>
void UITextPatchStream::set_texts(const T& t) {
    JsonUtil::to_json(m_j, t);
}

template void UITextPatchStream::set_texts<InGameUIText>(const InGameUIText& t);
template void UITextPatchStream::set_texts<SettingUIText>(const SettingUIText& t);
template void UITextPatchStream::set_texts<DialogUIText>(const DialogUIText& t);
