#include "copy_extractor.hpp"
#include "rikki/patcher/copy_patcher.hpp"

#include "utils/json_util.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    CopyExtractor
// ======================== C L A S S ========================

size_t CopyExtractor::extract() {
    if (!std::filesystem::create_directories(m_db)) {
        WvInvoker::log(LOG_LV_ERR, u8"Failed to create the copy directory");
        return 0;
    }

    if (!JsonUtil::save_into_file(nlohmann::json { }, path_t(m_db).append(CopyPatcher::FILE_NAME))) {
        WvInvoker::log(LOG_LV_ERR, u8"Failed to create the copy.json");
        return 0;
    }

    WvInvoker::log(LOG_LV_PROG, u8"Copy patch => OK");
    return 1;
}

CopyExtractor::CopyExtractor(const path_t& dst) :
    IExtractor(),
    m_db(path_t(dst).append(CopyPatcher::FOLDER_BASE)) { }
