#include "rixception.hpp"
#include "utils/string_util.hpp"

// ======================== C L A S S ========================
// ===    Rixception
// ======================== C L A S S ========================

Rixception::Rixception(const std::string& msg) :
    std::exception(msg.c_str()) { }

Rixception::Rixception(const std::u8string& msg) :
    std::exception(StringUtil::u8_to_cstr(msg)){ }

Rixception::Rixception(const char* msg) :
    std::exception(msg) { }

Rixception::Rixception(const char8_t* msg) :
    std::exception(StringUtil::u8_to_cstr(msg)) { }

// ======================== C L A S S ========================
// ===    ResourceRixception
// ======================== C L A S S ========================

ResourceRixception::ResourceRixception(const std::string& msg) :
    Rixception(msg.c_str()) { }

ResourceRixception::ResourceRixception(const std::u8string& msg) :
    Rixception(StringUtil::u8_to_cstr(msg)){ }

ResourceRixception::ResourceRixception(const char* msg) :
    Rixception(msg) { }

ResourceRixception::ResourceRixception(const char8_t* msg) :
    Rixception(StringUtil::u8_to_cstr(msg)) { }
