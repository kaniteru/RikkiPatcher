#ifndef RIKKI_PATCHER_RIKKI_EXTRACTOR_I_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_EXTRACTOR_I_EXTRACTOR_HPP
#include "precompiled.hpp"

// ======================== C L A S S ========================
// ===    IExtractor
// ======================== C L A S S ========================

class IExtractor {
public:
    virtual size_t extract() = 0;

public:
    /**
     * @param [in] dst Root path of custom patch data.
     */
    explicit IExtractor(const path_t& dst);
    virtual ~IExtractor() = default;
protected:
    const path_t m_dir; /* Root path of custom patch data. */
};


#endif //RIKKI_PATCHER_RIKKI_EXTRACTOR_I_EXTRACTOR_HPP
