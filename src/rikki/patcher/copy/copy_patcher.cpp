#include "copy_patcher.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/dir_mgr_enum.hpp"
#include "rikki/data/data_path.hpp"

#include "utils/json_util.hpp"

#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    CopyPatcher
// ======================== C L A S S ========================

PatcherResult CopyPatcher::patch() {
    PatcherResult result { };
    auto& ok        = result.m_ok;
    auto& failed  = result.m_failed;
    auto& passed = result.m_passed;

    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::PATCH_COPY_START);

    const auto file = path_t(m_db).append(CopyPath::CONFIG_FILE_NAME);

    if (!fs::exists(file)) {
        return { };
    }

    nlohmann::json j { };

    if (!JsonUtil::load_from_file(j, file)) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::PATCH_COPY_FAILED_READ);
        return { };
    }

    const auto& gmdir = DirMgr::get(DIR_GAME_BASE);

    for (const auto& [k, v] : j.items()) {
        const auto u8K = StringUtil::str_to_u8(k);
        const auto u8V = StringUtil::str_to_u8(v);

        if (u8K.empty() || u8V.empty()) {
            WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_COPY_FAILED_EMPTY, u8K, u8V);
            
            failed++;
            continue;
        }

        const path_t src = path_t(m_db).append(u8K);
        const path_t dst = path_t(gmdir).append(u8V);

        if (const auto parent = dst.parent_path(); !fs::exists(parent)) {
            fs::create_directory(parent);
        }

        bool success = false;
        bool isDir      = fs::is_directory(src);

        if (isDir) {
            try {
                fs::copy(src, dst, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
                success = true;
            } catch (const fs::filesystem_error& e) {
                WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::PATCH_COPY_FAILED_EXCEPTION, k, v, e.what());
            }
        } else {
            success = fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
        }

        if (success) {
            if (isDir) {
                WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_COPY_OK_DIR, k, v);
            } else {
                WvInvoker::log(WV_LOG_LV_PROG, WvLogFmt::PATCH_COPY_OK_FILE, k, v);
            }

            ok++;
        } else {
            failed++;
        }
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::PATCH_COPY_RESULT, result.total(), ok, failed, passed);
    return result;
}

PatcherResult CopyPatcher::migration() {
    return { };
}

PatcherResult CopyPatcher::extract() {
    WvInvoker::log(WV_LOG_LV_ALERT, WvLogFmt::EXTRACT_COPY_START);

    if (!fs::create_directories(m_db)) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_COPY_FAILED_WRITE);
        WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_COPY_RESULT, 1, 0, 1, 0);
        return { 0, 1, 0 };
    }

    if (!JsonUtil::save_into_file(nlohmann::json { }, path_t(m_db).append(CopyPath::CONFIG_FILE_NAME))) {
        WvInvoker::log(WV_LOG_LV_FATAL, WvLogFmt::EXTRACT_COPY_FAILED_WRITE);
        WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_COPY_RESULT, 1, 0, 1, 0);
        return { 0, 1, 0 };
    }

    WvInvoker::log(WV_LOG_LV_INFO, WvLogFmt::EXTRACT_COPY_RESULT, 1, 1, 0, 0);
    return { 1, 0, 0 };
}

CopyPatcher::CopyPatcher(const path_t& dir) :
    IPatcher(dir),
    m_db(path_t(dir) / CopyPath::PATCH_BASE) { }
