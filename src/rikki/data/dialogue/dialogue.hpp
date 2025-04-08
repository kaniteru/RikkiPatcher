#ifndef RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_DIALOGUE_HPP
#define RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_DIALOGUE_HPP
#include "precompiled.hpp"
#include "rikki/data/i_data.hpp"
#include "i_dialogue.hpp"

/* dialogue.hpp
 *  Included classes:
 *      - Dialogue
 */

// ======================== C L A S S ========================
// ===    Dialogue
// ======================== C L A S S ========================

/**
 * @brief Using load, modify and save the dialogue file. <br>
 * (asset/json/server/scene/*.json)
 *
 * @code
 * Dialogue dialogue(...);
 *
 * if (dialogue.is_valid()) { ... }
 * @endcode
 */
class Dialogue final : public IData, public IDialogue {
public:
    /**
     * @brief Save the data to the path where it was loaded.
     *
     * @return Returns true if saved successfully.
     */
    bool save() final;

    /**
     * @brief Save the data to the path provided in arg.
     *
     * @param path Target path.
     * @return Returns true if saved successfully.
     */
    bool save(const path_t& path) final;
private:
    /**
     * @brief iterate array elements in dialogue data.
     *
     * @param [in, out, optional] callback Retrieve or modify the data of elements.
     */
    void iterate_elements(const dialogue_iterate_t& callback) final;
public:
    /**
     * @brief Load dialogue from game data file.
     *
     * @param [in] file 'asset/json/server/scene/*.json' file path.
     */
    explicit Dialogue(const path_t& file);
private:
    const path_t m_file; /* Path of a target dialogue json file. */
    nlohmann::json m_j;  /* Loaded dialogue data. */
};


#endif //RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_DIALOGUE_HPP
