#ifndef RIKKI_PATCHER_RIKKI_DATA_PATCHER_HELPER_DIALOGUE_PATCH_HELPER_HPP
#define RIKKI_PATCHER_RIKKI_DATA_PATCHER_HELPER_DIALOGUE_PATCH_HELPER_HPP
#include "precompiled.hpp"
#include "rikki/patcher/i_patcher.hpp"
#include "rikki/data/dialogue/i_dialogue.hpp"

/* dialogue_patch_helper.hpp
 *  Included classes:
 *      - DialoguePatchHelper
 *      - ChoicePatchHelper
 *  Included structs:
 *      - DialoguePatchHelperResult
 */

// ======================== C L A S S ========================
// ===    DialoguePatchHelper
// ======================== C L A S S ========================

class DialoguePatchHelper {
public:
    /**
     * @brief Patch the dialogue data.
     *
     * @param [in] fPatch Target patch data file path.
     * @param [in] pDst Target dialogue ptr.
     * @return Returns patched data counts.
     */
    static PatcherResult do_patch(const path_t& fPatch, IDialogue* pDst);

    /**
     * @brief Migrate the patch file.
     *
     * @param [in] fPatch Target patch data file.
     * @param [in] fMigr Target migration data file.
     * @param [in] pureMap The pure dialogue map.
     * @return If save the patch file failed, returns DialoguePatchHelperResult::FAILED_SAVE.
     * <br>else if data doesn't exist in a pure map, returns DialoguePatchHelperResult::OK_NO_DATA. also, delete the patch file.
     */
    static PatcherResult do_migrate(const path_t& fPatch, const path_t& fMigr, const dialogue_map_t& pureMap);
};

// ======================== C L A S S ========================
// ===    ChoicePatchHelper
// ======================== C L A S S ========================

class ChoicePatchHelper {
public:
    /**
     * @brief Patch the choice data.
     *
     * @param [in] fPatch Target patch data file path.
     * @param [in] pDst Target dialogue ptr.
     * @return Returns patched data counts.
     */
    static PatcherResult do_patch(const path_t& fPatch, IDialogue* pDst);

    /**
     * @brief Migrate the patch file.
     *
     * @param [in] fPatch Target patch data file.
     * @param [in] fMigr Target migration data file.
     * @param [in] pureMap The pure dialogue map.
     * @return If save the patch file failed, returns DialoguePatchHelperResult::FAILED_SAVE.
     * <br>else if data doesn't exist in a pure map, returns DialoguePatchHelperResult::OK_NO_DATA. also, delete the patch file.
     */
    static PatcherResult do_migrate(const path_t& fPatch, const path_t& fMigr, const choice_map_t& pureMap);
};

// ======================= S T R U C T =======================
// ===    DialoguePatchHelperResult
// ======================= S T R U C T =======================

struct DialoguePatchHelperResult {
    static constexpr auto OK = 0;
    static constexpr auto OK_NO_DATA = 1;
    static constexpr auto FAILED_SAVE = -1;

    static auto to_result(const PatcherResult& r) {
        if (r == DialoguePatchHelperResult::PATCHER_RESULT_OK_NO_DATA) {
            return DialoguePatchHelperResult::OK_NO_DATA;
        }
        if (r == DialoguePatchHelperResult::PATCHER_RESULT_FAILED_SAVE) {
            return DialoguePatchHelperResult::FAILED_SAVE;
        }
        return DialoguePatchHelperResult::OK;
    }

    static constexpr PatcherResult PATCHER_RESULT_OK_NO_DATA =  { 0, 1, 0, 0 };
    static constexpr PatcherResult PATCHER_RESULT_FAILED_SAVE = { 0, 0, 1, 0 };
};


#endif //RIKKI_PATCHER_RIKKI_DATA_PATCHER_HELPER_DIALOGUE_PATCH_HELPER_HPP
