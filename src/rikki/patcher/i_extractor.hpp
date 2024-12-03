#ifndef RIKKI_PATCHER_RIKKI_PATCHER_I_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_I_EXTRACTOR_HPP
#include "precompiled.hpp"
#include "i_patcher.hpp"

class IExtractor : public IRikkiPatcher {
public:
    virtual size_t extract() = 0;

public:
    explicit IExtractor(const path_t& dir);
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_I_EXTRACTOR_HPP
