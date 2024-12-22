#ifndef RIKKI_PATCHER_RIKKI_DATA_I_DATA_HPP
#define RIKKI_PATCHER_RIKKI_DATA_I_DATA_HPP
#include "precompiled.hpp"

class IData {
public:
    bool is_valid();

    virtual bool backup(const path_t& dir) = 0;
    virtual bool save() = 0;
    virtual bool save(const path_t& dir) = 0;

public:
    virtual ~IData() = default;
protected:
    bool m_isValid = false;
};


#endif //RIKKI_PATCHER_RIKKI_DATA_I_DATA_HPP
