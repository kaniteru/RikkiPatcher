#ifndef RIKKI_PATCHER_UTILS_REGISTRY_READER_HPP
#define RIKKI_PATCHER_UTILS_REGISTRY_READER_HPP
#include "precompiled.hpp"

// ======================== C L A S S ========================
// ===    RegistryReader
// ======================== C L A S S ========================

class RegistryReader {
public:
    bool is_valid() const;

    std::wstring read_string(std::wstring_view key);
    std::wstring read_multi_string(std::wstring_view key);
    DWORD read_dword(std::wstring_view key);
    std::vector<BYTE> read_binary(std::wstring_view key);
private:
    template<class T>
    bool query(std::wstring_view key, DWORD type, T* pValue);

public:
    explicit RegistryReader(std::wstring_view path);
    ~RegistryReader();
private:
    bool m_isValid;
    HKEY m_hKey;
};


#endif //RIKKI_PATCHER_UTILS_REGISTRY_READER_HPP
