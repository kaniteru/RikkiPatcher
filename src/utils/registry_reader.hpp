#ifndef RIKKI_PATCHER_UTILS_REGISTRY_READER_HPP
#define RIKKI_PATCHER_UTILS_REGISTRY_READER_HPP
#include "precompiled.hpp"

/* registry_reader.hpp
 *  Included classes:
 *      - RegistryReader
 */

// ======================== C L A S S ========================
// ===    RegistryReader
// ======================== C L A S S ========================

/**
 * @brief Windows Registry reader for HKEY_CURRENT_USER.
 */
class RegistryReader {
public:
    /**
     * @brief Check if a registry key was opened successfully.
     *
     * @return true if opened successfully, false otherwise.
     */
    [[nodiscard]]
    bool is_valid() const;

    /**
     * @brief Read string value.
     *
     * @param key Value name.
     * @return Value string, empty if not found.
     */
    [[nodiscard]]
    std::wstring read_string(std::wstring_view key);

    /**
     * @brief Read DWORD value.
     *
     * @param key Value name.
     * @return Value, 0 if not found.
     */
    [[nodiscard]]
    DWORD read_dword(std::wstring_view key);

    /**
     * @brief Read binary value.
     *
     * @param key Value name.
     * @return Value bytes, empty if not found.
     */
    [[nodiscard]]
    std::vector<BYTE> read_binary(std::wstring_view key);
private:
    template<class T> [[nodiscard]]
    bool query(std::wstring_view key, DWORD type, T* pValue);

public:
    explicit RegistryReader(std::wstring_view path);
    ~RegistryReader();
private:
    bool m_isValid;
    HKEY m_hKey;
};


#endif //RIKKI_PATCHER_UTILS_REGISTRY_READER_HPP
