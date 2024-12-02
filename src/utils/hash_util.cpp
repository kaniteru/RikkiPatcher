#include "hash_util.hpp"

std::string HashUtil::file_to_hash(const path_t& file) {
    std::string result { };

    if (auto fs = std::fstream(file, std::ios::in); fs.is_open()) {
        std::stringstream ss { };
        ss << fs.rdbuf();

        SHA512 sha;
        result = sha.hash(ss.str());
        fs.close();
    }

    return result;
}
