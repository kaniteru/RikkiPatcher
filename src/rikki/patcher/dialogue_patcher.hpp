#ifndef RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_PATCHER_HPP
#include "precompiled.hpp"
#include "i_patcher.hpp"
#include "rikki/data/dialogue.hpp"

// ======================== C L A S S ========================
// ===    DialoguePatcher
// ======================== C L A S S ========================

class DialoguePatcher : public IPatcher {
public:
    /**
     * @brief Do custom patch into game data.
     *
     * @return Returns patched files count.
     */
    size_t patch() final;

    /**
     * @brief Migrate custom data using game data.
     *             Game data must be unmodified.
     *
     * @return Returns true if migrated successfully.
     */
    bool migration() final;
private:
    /**
     * @brief Generate migration info data.
     *             This data will be used to migrate custom patch data to match the updated game in the future.
     *             Game data must be unmodified.
     *
     * @return
     */
    bool generate_migration_info() final;

public:
    /**
     * @brief Initialize using custom data directory.
     *
     * @param [in] src Custom data directory path.
     */
    explicit DialoguePatcher(const path_t& src);
private:
    path_t m_dataBase;
    path_t m_migrBase;

    constexpr static auto FOLDER_BASE = "dialogues";
    constexpr static auto FILE_SPEAKERS = "speakers.json";
};

// ======================== C L A S S ========================
// ===    SpeakerPatchStream
// ======================== C L A S S ========================

class SpeakerPatchStream {
public:
    /**
     * @brief Get speakers from data.
     *
     * @return Returns speakers map.
     */
    speaker_map_t get_speakers() const;

    /**
     * @brief Check target speaker is exists.
     *
     * @param [in] spk Target speaker.
     * @return Returns true if target spaeakr exists
     */
    bool is_spekaer_exists(std::string_view spk) const;

    /**
     * @brief Set speakers in data.
     *
     * @param [in] map Speakers map.
     */
    void set_speakers(const speaker_map_t& map);

    /**
     * @brief Remove target speaker from data.
     *
     * @param [in] spk Target speaker.
     * @return Returns false if target speaker doesn't exist in data.
     */
    bool remove_spekaer(std::string_view spk);

    /**
     * @brief Save data into file.
     *
     * @return Returns ture if data saved successfully.
     */
    bool save() const;

public:
    /**
      * @brief Load speakers from custom path file.
      *
      * @param [in] file Speaker custom patch file path.
      */
     explicit SpeakerPatchStream(const path_t& file);
private:
    path_t m_file;
    nlohmann::json m_j;
};

// ======================== C L A S S ========================
// ===    DialoguePatchStream
// ======================== C L A S S ========================

class DialoguePatchStream {
public:
    /**
     * @brief Find dialogue using index.
     *
     * @param [in] idx Target dialogue index.
     * @return Returns target index dialogue.
     */
    DialogueEntry get_dialogue(dialogue_idx_t idx) const;

    /**
     * @brief Get loaded dialogues.
     *
     * @return Returns loaded dialogue map.
     */
    dialogue_map_t get_dialogues() const;

    /**
     * @brief Check target index dialogue is exist.
     *
     * @param [in] idx Target dialogue index.
     * @return Returns true if dialogue exists.
     */
    bool is_idx_exists(dialogue_idx_t idx) const;

    /**
     * @brief Set dialogues in data.
     *
     * @param [in] map Dialogues map.
     */
    void set_dialogues(const dialogue_map_t& map);

    /**
     * @brief Remove dialogue using index.
     *
     * @param [in] idx Target dialogue index.
     */
    void remove_dialogue(dialogue_idx_t idx);

    /**
     * @brief Save data into file.
     *
     * @return Returns ture if data saved successfully.
     */
    bool save() const;

public:
    /**
     * @brief Load dialogues from custom patch file.
     *
     * @param [in] file Dialogue custom path file path.
     */
    explicit DialoguePatchStream(const path_t& file);
private:
    path_t m_file;
    nlohmann::json m_j;

    constexpr static auto KEY_SPEAKER = "speaker";
    constexpr static auto KEY_DIALOGUE = "dialogue";
};

// ======================== C L A S S ========================
// ===    DialogueMigrStream
// ======================== C L A S S ========================

class DialogueMigrStream {
public:
    /**
     * @brief Check is migration data loaded successfully.
     *
     * @return Returns true if data loaded successfully.
     */
    bool is_valid() const;

    /**
     * @brief Get pure dialogue file hash.
     *
     * @return Returns pure dialogue file hash.
     */
    std::string get_file_hash() const;

    /**
     * @brief Get pure dialogue entries.
     *
     * @return Returns pure dialogue entries.
     */
    dialogue_map_t get_dialogues() const;

public:
    /**
     * @brief Get pure speakers from speakers migration data file.
     *             File name is 'FILE_SPEAKERS'.
     *
     * @param [in] file Speakers migration data file path.
     * @return Pure speakers.
     */
    static std::vector<std::string> get_spekaers(const path_t& file);

    /**
     * @brief Save migration data files.
     *             Game data must be unmodified.
     *
     * @param [in] dir Path to save the migration data files.
     * @return
     */
    static void save_migration_data(const path_t& dir);

    /**
     * @brief Load migration data from file.
     *
     * @param [in] file Migration data file path.
     */
    explicit DialogueMigrStream(const path_t& file);
private:
    bool m_isValid;
    nlohmann::json m_j;

    constexpr static auto KEY_HASH = "hash";
    constexpr static auto KEY_LIST = "list";
    constexpr static auto KEY_SPEAKER    = "speaker";
    constexpr static auto KEY_DIALOGUE = "dialogue";

    constexpr static auto FILE_SPEAKERS = "speakers.json";

    friend class DialoguePatcher;
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_PATCHER_HPP
