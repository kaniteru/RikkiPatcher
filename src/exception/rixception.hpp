#ifndef RIKKI_PATCHER_EXCEPTION_RIXCEPTION_HPP
#define RIKKI_PATCHER_EXCEPTION_RIXCEPTION_HPP
#include "precompiled.hpp"

/* rixception.hpp
 *  Included classes:
 *      - Rixception
 */

// ======================== C L A S S ========================
// ===    Rixception
// ======================== C L A S S ========================

class Rixception : public std::exception {
public:
    explicit Rixception(const std::string& msg);
    explicit Rixception(const std::u8string& msg);
    explicit Rixception(const char* msg);
    explicit Rixception(const char8_t* msg);
    ~Rixception() override = default;
};

// ======================== C L A S S ========================
// ===    ResourceRixception
// ======================== C L A S S ========================

class ResourceRixception final : public Rixception {
public:
    explicit ResourceRixception(const std::string& msg);
    explicit ResourceRixception(const std::u8string& msg);
    explicit ResourceRixception(const char* msg);
    explicit ResourceRixception(const char8_t* msg);
    ~ResourceRixception() override = default;
};


#endif //RIKKI_PATCHER_EXCEPTION_RIXCEPTION_HPP
