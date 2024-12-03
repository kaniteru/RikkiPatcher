#include "lang.hpp"
#include "utils/json_util.hpp"

Lang::Lang(const path_t& path) {
    JsonUtil::load_from_file(m_j, path);
}