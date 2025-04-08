#include "registry_reader.hpp"

// ======================== C L A S S ========================
// ===    RegistryReader
// ======================== C L A S S ========================

bool RegistryReader::is_valid() const {
    return m_isValid;
}

std::wstring RegistryReader::read_string(std::wstring_view key) {
    std::wstring result { };
    this->query(key, REG_SZ, &result);
    return result;
}

std::wstring RegistryReader::read_multi_string(std::wstring_view key) {
    std::wstring result { };
    this->query(key, REG_MULTI_SZ, &result);
    return result;
}

DWORD RegistryReader::read_dword(std::wstring_view key) {
    DWORD result = 0;
    this->query(key, REG_DWORD, &result);
    return result;
}

std::vector<BYTE> RegistryReader::read_binary(std::wstring_view key) {
    std::vector<BYTE> result { };
    this->query(key, REG_BINARY, &result);
    return result;
}

template<class T>
bool RegistryReader::query(std::wstring_view key, DWORD type, T* pValue) {
    if (!m_hKey || !pValue) {
        return false;
    }

    DWORD size = 0;
    LONG lRes = RegQueryValueEx(m_hKey, key.data(), nullptr, &type, nullptr, &size);

    if (lRes != ERROR_SUCCESS) {
        return false;
    }

    std::vector<BYTE> buf(size);
    lRes = RegQueryValueEx(m_hKey, key.data(), nullptr, &type, buf.data(), &size);

    if (lRes != ERROR_SUCCESS) {
        return false;
    }

    if constexpr (std::is_same_v<T, std::wstring>) {
        *pValue = reinterpret_cast<wchar_t*>(buf.data());
    }
    else if constexpr (std::is_same_v<T, DWORD>) {
        *pValue = *reinterpret_cast<DWORD*>(buf.data());
    }
    else if constexpr (std::is_same_v<T, std::vector<BYTE>>) {
        *pValue = std::move(buf);
    }
    else {
        return false;
    }

    return true;
}

RegistryReader::RegistryReader(std::wstring_view path) :
    m_isValid(false),
    m_hKey(nullptr) {

    auto lRes = RegOpenKeyEx(HKEY_CURRENT_USER, path.data(), 0, KEY_READ, &m_hKey);
    m_isValid = lRes == ERROR_SUCCESS;
}

RegistryReader::~RegistryReader() {
    if (m_hKey) {
        RegCloseKey(m_hKey);
        m_hKey = nullptr;
    }
}
