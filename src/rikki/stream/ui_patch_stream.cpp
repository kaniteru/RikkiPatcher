#include "ui_patch_stream.hpp"
#include "utils/json_util.hpp"

void UITextPatchStream::clear() {
    m_j.clear();
}

bool UITextPatchStream::save() const {
    return JsonUtil::save_into_file(m_j, m_file);
}

UITextPatchStream::UITextPatchStream(const path_t& file) :
    m_file(file) { }
