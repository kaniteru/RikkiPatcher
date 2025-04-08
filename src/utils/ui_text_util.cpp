#include "ui_text_util.hpp"

#include "rikki/dir_mgr.hpp"
#include "rikki/dir_mgr_enum.hpp"

#include "utils/logger.hpp"
#include "utils/sevenzip_util.hpp"

// ======================== C L A S S ========================
// ===    UITextUtil
// ======================== C L A S S ========================

bool UITextUtil::copy_startup_from_game_and_decrypt(path_t& file) {
    const auto tempDir = path_t(DirMgr::get(DIR_PROJ_TEMP)).append(TEMP_FOLDER_NAME);
    const auto fGm     = DirMgr::get(DIR_GAME_JSON_STARTUP);
    const auto fZip       = path_t(tempDir).append(ZIP_FILE_NAME);
    const auto fPatch   = path_t(tempDir).append(FILE_NAME);

    fs::remove_all(tempDir);

    if (!fs::create_directories(tempDir)) {
        LOG(FATAL, "failed to create temp/ui dir");
        return false;
    }

    // copy the game file to temp dir
    if (!fs::copy_file(fGm, fZip, fs::copy_options::overwrite_existing)) {
        LOG(FATAL, "failed to copy startup.json from game");
        return false;
    }

    const SevenzipUtil svzip(DirMgr::get(DIR_PROJ_EXE_7ZIP));

    // decrypt the game file
    if (!svzip.unzip(fZip, tempDir, true, PW)) {
        LOG(FATAL, "failed to decrypt startup.json");
        return false;
    }

    file = path_t(tempDir).append(FILE_NAME);
    return true;
}

bool UITextUtil::encrypt_startup_and_move_to_game() {
    const auto tempDir = path_t(DirMgr::get(DIR_PROJ_TEMP)).append(TEMP_FOLDER_NAME);
    const auto fGm     = DirMgr::get(DIR_GAME_JSON_STARTUP);
    const auto fZip       = path_t(tempDir).append(ZIP_FILE_NAME);
    const auto fPatch   = path_t(tempDir).append(FILE_NAME);

    if (!fs::exists(tempDir) || !fs::exists(fZip)) {
        LOG(FATAL, "temp dir or zip file not found");
        fs::remove_all(tempDir);
        return false;
    }

    const SevenzipUtil svzip(DirMgr::get(DIR_PROJ_EXE_7ZIP));

    // re-zip patched file
    if (!svzip.zip({ fPatch }, fZip, true, PW)) {
        LOG(FATAL, "failed to re-zip patched file");
        fs::remove_all(tempDir);
        return false;
    }

    // copy patched file to game dir
    if (!fs::copy_file(fZip, fGm, fs::copy_options::overwrite_existing)) {
        LOG(FATAL, "failed to copy patched file to game dir");
        fs::remove_all(tempDir);
        return false;
    }

    fs::remove_all(tempDir);
    return true;
}
