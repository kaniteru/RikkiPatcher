#include "filesystem_util.hpp"

std::vector<path_t> FilesystemUtil::sort_files(const path_t& dir) {
    std::vector<path_t> result { };

    for (const auto& it : std::filesystem::directory_iterator(dir)) {
        result.push_back(it.path());
    }

    std::sort(result.begin(), result.end(), FilesystemUtil::natural_sort_comparator);
    return result;
}

void FilesystemUtil::delete_and_create_directories(const path_t& dir) {
    try {
        std::filesystem::remove_all(dir);
    }
    catch (const std::exception& e) { }

    std::filesystem::create_directories(dir);
}

std::vector<int32_t> FilesystemUtil::extract_nums(std::u8string_view filename) {
    static const auto REGEX = std::regex("(\\d+)");

    std::vector<int32_t> result { };
    std::string utf8 = reinterpret_cast<const char*>(filename.data());

    std::sregex_iterator it(utf8.begin(), utf8.end(), REGEX);
    std::sregex_iterator end { };

    while (it != end) {
        result.push_back(std::stoi((*it).str()));
        ++it;
    }

    return result;
}

bool FilesystemUtil::natural_sort_comparator(const path_t& a, const path_t& b) {
    auto numbersA = FilesystemUtil::extract_nums(a.filename().u8string());
    auto numbersB = FilesystemUtil::extract_nums(b.filename().u8string());

    if (numbersA.empty() && numbersB.empty()) {
        return a.filename() < b.filename();
    } else if (numbersA.empty()) {
        return true;
    } else if (numbersB.empty()) {
        return false;
    } else {
        return numbersA < numbersB;
    }
}
