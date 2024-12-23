#include "sevenzip_util.hpp"

#include "string_util.hpp"

bool SevenzipUtil::zip(const std::vector<path_t>& files, const path_t& dst, bool usePW, const std::u8string& pw) const {
    auto cmd = this->get_cmd_prefix()
    + u8"a "
    + SevenzipUtil::quote(dst.generic_u8string(), true);

    for (const auto& f : files) {
        cmd += SevenzipUtil::quote(f.generic_u8string(), true);
    }

    if (usePW) {
        cmd += u8"-p"
        + SevenzipUtil::quote(pw, true);
    }

    cmd += u8"-y";
    return system(StringUtil::u8_to_cstr(cmd)) == 0;
}

bool SevenzipUtil::unzip(const path_t& src, const path_t& dst, bool usePW, const std::u8string& pw) const {
    auto cmd = this->get_cmd_prefix()
    + u8"x "
    + SevenzipUtil::quote(src.generic_u8string(), true)
    + u8"-o"
    + SevenzipUtil::quote(dst.generic_u8string(), true);

    if (usePW) {
        cmd += u8"-p"
        + SevenzipUtil::quote(pw, true);
    }

    cmd += u8"-aoa";
    return system(StringUtil::u8_to_cstr(cmd)) == 0;
}

constexpr std::u8string SevenzipUtil::quote(const std::u8string& s, const bool addSpace) {
    return u8"\"" + s + u8"\"" + (addSpace ? u8" " : u8"");
}

std::u8string SevenzipUtil::get_cmd_prefix() const {
    return m_svzaPath.generic_u8string() + u8" ";
}

SevenzipUtil::SevenzipUtil(const path_t& svzaPath) :
    m_svzaPath(svzaPath) { }
