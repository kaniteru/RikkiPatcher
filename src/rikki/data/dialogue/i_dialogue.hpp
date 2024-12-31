#ifndef RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_I_DIALOGUE_HPP
#define RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_I_DIALOGUE_HPP
#include "precompiled.hpp"

/* i_dialogue.hpp
 *  Included classes:
 *      - IDialogue
 */

namespace j {
struct Dialogue;
struct DialogueSpan;
struct Choice;
}

using dialogue_idx_t = uint64_t; /* Dialogue index. */
using choice_idx_t    = uint64_t; /* Choice index. */

using dialogue_map_t = std::map<dialogue_idx_t, j::Dialogue>;
using choice_map_t    = std::map<choice_idx_t, j::Choice>;

using dialogue_iterate_t  = std::function<void(const int64_t elementID, nlohmann::basic_json<>& array)>;
using dialogue_callback_t = std::function<void(const dialogue_idx_t idx, j::Dialogue& dia)>;
using choices_callback_t  = std::function<void(const choice_idx_t idx, j::Choice& choice)>;

// ======================== C L A S S ========================
// ===    IDialogue
// ======================== C L A S S ========================

class IDialogue {
public:
    /**
     * @brief Extract all existing dialogues from data.
     *
     * @return Existing dialogues data map.
     */
    dialogue_map_t extract_dialogues();

    /**
     * @brief Extract all existing choices from data.
     *
     * @return Existing choices data map.
     */
    choice_map_t extract_choices();

    /**
     * @brief Modify the dialogues data.
     *
     * @param [in] entries Map of data to be modified.
     * @return Successfully modified dialogue indexes.
     */
    std::vector<dialogue_idx_t> update_dialogues(const dialogue_map_t& entries);

    /**
     * @brief Modify the choices data.
     *
     * @param [in] entries Map of data to be modified.
     * @return Successfully modified choice indexes.
     */
    std::vector<choice_idx_t> update_choices(const choice_map_t& entries);
protected:
    virtual void iterate_elements(const dialogue_iterate_t& callback) = 0;
     /**
     * @brief Perform a for-each on the loaded dialogue data.
     *             Can get index and modify the data of spekaer and diagloue string.
     *
     * @param [in, out, optional] callback Retrieve or modify the data of spekaer and diagloue string.
     */
    void find_dialogues(const dialogue_callback_t& callback);

     /**
     * @brief Perfomr a for-each on the loaded choice data.
     *             Can get index and modify the data of choice string.
     *
     * @param [in, out, optional] callback Retrieve or modify the data of choice string.
     */
    void find_choices(const choices_callback_t& callback);

public:
    virtual ~IDialogue() = default;
};


#endif //RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_I_DIALOGUE_HPP
