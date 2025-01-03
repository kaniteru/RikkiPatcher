#include "i_stream.hpp"
#include "utils/json_util.hpp"

// ======================== C L A S S ========================
// ===    IRikkiStream
// ======================== C L A S S ========================

bool IRikkiStream::is_loaded() const {
    return m_isLoaded;
}

void IRikkiStream::clear() {
    m_j.clear();
}

bool IRikkiStream::save() const {
    return JsonUtil::save_into_file(m_j, m_file);
}

IRikkiStream::IRikkiStream(const path_t& file) :
    m_file(file) {

    m_isLoaded = JsonUtil::load_from_file(m_j, m_file);
}
