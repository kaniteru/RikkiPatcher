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
    virtual ~IExtractor() = default;
};


#endif //RIKKI_PATCHER_RIKKI_EXTRACTOR_I_EXTRACTOR_HPP
