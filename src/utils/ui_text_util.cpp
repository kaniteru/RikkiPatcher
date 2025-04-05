#include "ui_text_util.hpp"
#include "rikki/dir_mgr.hpp"

#include "utils/sevenzip_util.hpp"
#include "utils/temp_dir_mutex.hpp"

// ======================== C L A S S ========================
// ===    UITextUtil
// ======================== C L A S S ========================

bool UITextUtil::copy_startup_from_game_and_decrypt(path_t& file) {
    if (!INSTFAC(TempDirMutex)->lock(TEMP_FOLDER_NAME)) {
        return false;
    }

    const auto tempDir = path_t(INSTFAC(DirMgr)->get(DIR_PROJ_TEMP)).append(TEMP_FOLDER_NAME);
    const auto fGm = INSTFAC(DirMgr)->get(DIR_GAME_JSON_STARTUP);
    const auto fZip = path_t(tempDir).append(ZIP_FILE_NAME);
    const auto fPatch = path_t(tempDir).append(FILE_NAME);

    // copy the game file to temp dir
    if (!std::filesystem::copy_file(fGm, fZip, std::filesystem::copy_options::overwrite_existing)) {
        INSTFAC(TempDirMutex)->unlock(TEMP_FOLDER_NAME);
        return false;
    }

    const SevenzipUtil svzip(INSTFAC(DirMgr)->get(DIR_PROJ_EXE_7ZIP));

    // decrypt the game file
    if (!svzip.unzip(fZip, tempDir, true, PW)) {
        INSTFAC(TempDirMutex)->unlock(TEMP_FOLDER_NAME);
        return false;
    }

    file = path_t(tempDir).append(FILE_NAME);
    return true;
}

bool UITextUtil::encrypt_startup_and_move_to_game() {
    if (!INSTFAC(TempDirMutex)->is_locked(TEMP_FOLDER_NAME)) {
        return false;
    }

    const auto tempDir = path_t(INSTFAC(DirMgr)->get(DIR_PROJ_TEMP)).append(TEMP_FOLDER_NAME);
    const auto fGm = INSTFAC(DirMgr)->get(DIR_GAME_JSON_STARTUP);
    const auto fZip = path_t(tempDir).append(ZIP_FILE_NAME);
    const auto fPatch = path_t(tempDir).append(FILE_NAME);

    const SevenzipUtil svzip(INSTFAC(DirMgr)->get(DIR_PROJ_EXE_7ZIP));

    // re-zip patched file
    if (!svzip.zip({ fPatch }, fZip, true, PW)) {
        INSTFAC(TempDirMutex)->unlock(TEMP_FOLDER_NAME);
        return false;
    }

    // copy patched file to game dir
    if (!std::filesystem::copy_file(fZip, fGm, std::filesystem::copy_options::overwrite_existing)) {
        INSTFAC(TempDirMutex)->unlock(TEMP_FOLDER_NAME);
        return false;
    }

    INSTFAC(TempDirMutex)->unlock(TEMP_FOLDER_NAME);
    return true;
}
