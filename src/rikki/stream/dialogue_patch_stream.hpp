#ifndef RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_STREAM_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_STREAM_HPP
#include "precompiled.hpp"
#include "rikki/data/dialogue.hpp"

/*dialogue_patch_stream.hpp
 * Included classes:
 *     - DialoguePatchStream
 *     - ChoicePatchStream
 *     - [unused] SpeakerPatchStream
 */

// ======================== C L A S S ========================
// ===    DialoguePatchStream
// ======================== C L A S S ========================

class DialoguePatchStream {
public:
    /**
     * @brief Find dialogue from index.
     *
     * @param [in] idx Target dialogue index.
     * @return Returns target dialogue of index.
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
     * @brief Clear dialogues from loaded data.
     */
    void clear();

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
    nlohmann::ordered_json m_j;

    constexpr static auto KEY_SPEAKER = "speaker";
    constexpr static auto KEY_DIALOGUE = "dialogue";
};

// ======================== C L A S S ========================
// ===    ChoicePatchStream
// ======================== C L A S S ========================

class ChoicePatchStream {
public:
    /**
     * @brief Find choice from index.
     *
     * @param  [in] idx Target choice index.
     * @return Returns target choice of index.
     */
    std::string get_choice(choice_idx_t idx) const;

    /**
     * @brief Get loaded choices.
     *
     * @return Returns loaded choice map.
    */
    choice_map_t get_choices() const;

    bool is_idx_exists(choice_idx_t idx) const;

    void set_choices(const choice_map_t& map);

    void remove_choice(choice_idx_t idx);

    void clear();

    bool save() const;

public:
    explicit ChoicePatchStream(const path_t& file);
private:
    path_t m_file;
    nlohmann::ordered_json m_j;
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
     * @return Returns true if target speaker exists.
     */
   bool is_speaker_exists(std::string_view spk) const;

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
    bool remove_speaker(std::string_view spk);

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

    SpeakerPatchStream() = default;
private:
    path_t m_file;
    nlohmann::json m_j;
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_STREAM_HPP
