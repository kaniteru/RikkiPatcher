#include "copy_patcher.hpp"
#include "rikki/dir_mgr.hpp"
#include "utils/json_util.hpp"
#include "utils/instance_factory.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    CopyPatcher
// ======================== C L A S S ========================

PatcherResult CopyPatcher::patch() {
    PatcherResult result { };
    size_t& total =  result.m_total;
    size_t& ok = result.m_ok;
    size_t& failed = result.m_failed;
    size_t& passed = result.m_passed;

    const auto file = path_t(m_db).append(FILE_NAME);

    if (!std::filesystem::exists(file)) {
        return { };
    }

    nlohmann::json j { };

    if (!JsonUtil::load_from_file(j, file)) {
        WvInvoker::log(LOG_LV_ERR, "Can't read the copy.json file");
        return { };
    }

    const auto& gmdir = INSTFAC(DirMgr)->get(DIR_GAME_BASE);

    for (const auto& [k, v] : j.items()) {
        const auto u8K = StringUtil::str_to_u8(k);
        const auto u8V = StringUtil::str_to_u8(v);
        total++;

        if (u8K.empty() || u8V.empty()) {
            WvInvoker::log(LOG_LV_PROG, "Empty src or dst => Failed");
            failed++;
            continue;
        }

        const path_t src = path_t(m_db).append(u8K);
        const path_t dst = path_t(gmdir).append(u8V);

        if (const auto parent = dst.parent_path(); !std::filesystem::exists(parent)) {
            std::filesystem::create_directory(parent);
        }

        bool success = false;
        auto log = src.filename().generic_u8string() + u8" [";

        if (std::filesystem::is_directory(src)) {
            log += u8"directory] => ";
            try {
                std::filesystem::copy(src, dst, std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
                success = true;
            } catch (const std::filesystem::filesystem_error& e) { }

        } else {
            log += u8"file] => ";
            success = std::filesystem::copy_file(src, dst, std::filesystem::copy_options::overwrite_existing);
        }

        if (!success) {
            log += u8"Failed";
            failed++;
        } else {
            log += u8"OK";
            ok++;
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    const std::string log = "Total: " + std::to_string(total) + " | ok: " + std::to_string(ok) + " | passed: " + std::to_string(passed)
                            + " | failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
    return result;
}

PatcherResult CopyPatcher::migration() {
    return { };
}

PatcherResult CopyPatcher::generate_migration_info() {
    return { };
}

CopyPatcher::CopyPatcher(const path_t& dir) :
    IPatcher(dir),
    m_db(path_t(dir).append(FOLDER_BASE)) { }
