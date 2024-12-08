#ifndef RIKKI_PATCHER_RIKKI_PATCHER_I_STREAM_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_I_STREAM_HPP
#include "precompiled.hpp"

// ======================== C L A S S ========================
// ===    IMigrStream
// ======================== C L A S S ========================

class IMigrStream {
public:
    /**
     * @brief Check is migration data loaded successfully.
     *
     * @return Returns true if data loaded successfully.
     */
    bool is_valid() const;

protected:
    bool m_isValid;
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_I_STREAM_HPP
