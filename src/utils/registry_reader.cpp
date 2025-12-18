#include "registry_reader.hpp"
#include "logger.hpp"
#include "utils/string_util.hpp"

// ======================== C L A S S ========================
// ===    RegistryReader
// ======================== C L A S S ========================

bool RegistryReader::is_valid() const {
    return m_isValid;
}

std::wstring RegistryReader::read_string(const std::wstring_view key) {
    std::wstring result { };
    (void)this->query(key, REG_SZ, &result);
    return result;
}

DWORD RegistryReader::read_dword(const std::wstring_view key) {
    DWORD result = 0;
    (void)this->query(key, REG_DWORD, &result);
    return result;
}

std::vector<BYTE> RegistryReader::read_binary(const std::wstring_view key) {
    std::vector<BYTE> result { };
    (void)this->query(key, REG_BINARY, &result);
    return result;
}

template<class T>
bool RegistryReader::query(const std::wstring_view key, DWORD type, T* pValue) {
    if (!m_hKey || !pValue) {
        return false;
    }

    DWORD size = 0;

    if (RegQueryValueEx(m_hKey, key.data(), nullptr, &type, nullptr, &size) != ERROR_SUCCESS) {
        LOG_FATAL("Failed to query registry key: {}", StringUtil::wstr_to_str(key));
        return false;
    }

    std::vector<BYTE> buf(size);

    if (RegQueryValueEx(m_hKey, key.data(), nullptr, &type, buf.data(), &size) != ERROR_SUCCESS) {
        LOG_FATAL("Failed to query registry key: {}", StringUtil::wstr_to_str(key));
        return false;
    }

    if constexpr (std::is_same_v<T, std::wstring>) {
        *pValue = reinterpret_cast<wchar_t*>(buf.data());
    } else if constexpr (std::is_same_v<T, DWORD>) {
        *pValue = *reinterpret_cast<DWORD*>(buf.data());
    } else if constexpr (std::is_same_v<T, std::vector<BYTE>>) {
        *pValue = std::move(buf);
    } else {
        return false;
    }

    return true;
}

RegistryReader::RegistryReader(const std::wstring_view path) :
    m_isValid(false),
    m_hKey(nullptr) {

    const auto lRes = RegOpenKeyEx(HKEY_CURRENT_USER, path.data(), 0, KEY_READ, &m_hKey);
    m_isValid = lRes == ERROR_SUCCESS;
}

RegistryReader::~RegistryReader() {
    if (m_hKey) {
        RegCloseKey(m_hKey);
        m_hKey = nullptr;
    }
}
