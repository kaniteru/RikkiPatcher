#ifndef RIKKI_PATCHER_UTILS_SEVENZIP_UTIL_HPP
#define RIKKI_PATCHER_UTILS_SEVENZIP_UTIL_HPP
#include "precompiled.hpp"

// ======================== C L A S S ========================
// ===    SevenzipUtil
// ======================== C L A S S ========================

class SevenzipUtil {
public:
    bool zip(const std::vector<path_t>& files, const path_t& dst, bool usePW, const std::u8string& pw) const;
    bool unzip(const path_t& src, const path_t& dst, bool usePW, const std::u8string& pw) const;
private:
    /**
     * @brief Get svzaPath to string.
     *
     * @return Returns "m_svzaPath"
     */
    static constexpr std::u8string quote(const std::u8string& s, bool addSpace = false);
    std::u8string get_cmd_prefix() const;

public:
    /**
     * @param [in] svzaPath 7za.exe path
     */
    explicit SevenzipUtil(const path_t& svzaPath);
private:
    path_t m_svzaPath;
};


#endif //RIKKI_PATCHER_UTILS_SEVENZIP_UTIL_HPP
