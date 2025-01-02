#ifndef RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_STREAM_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_STREAM_HPP
#include "precompiled.hpp"
#include "i_stream.hpp"
#include "rikki/data/dialogue/dialogue.hpp"

/*dialogue_patch_stream.hpp
 * Included classes:
 *     - DialoguePatchStream
 *     - ChoicePatchStream
 */

// ======================== C L A S S ========================
// ===    DialoguePatchStream
// ======================== C L A S S ========================

class DialoguePatchStream final : public IRikkiStream {
public:
    /**
     * @brief Find dialogue from index.
     *
     * @param [in] idx Target dialogue index.
     * @param [out] e Result reference.
     * @return Returns true if target dialogue exists.
     */
    bool get_dialogue(dialogue_idx_t idx, j::Dialogue& e) const;

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

public:
    /**
     * @brief Load dialogues from custom patch file.
     *
     * @param [in] file Dialogue custom patch file path.
     */
    explicit DialoguePatchStream(const path_t& file);
};

// ======================== C L A S S ========================
// ===    ChoicePatchStream
// ======================== C L A S S ========================

class ChoicePatchStream final : public IRikkiStream {
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

public:
    explicit ChoicePatchStream(const path_t& file);
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_STREAM_HPP
