#ifndef RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_HPP
#define RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_HPP
#include "precompiled.hpp"
#include "i_data.hpp"

/* dialogue.hpp
 *  Included classes:
 *      - Dialogue
 *
 *  Included structs:
 *      - DialogueEntry
 *      - DialogueSpan
 */

struct DialogueEntry;
struct DialogueSpan;

using dialogue_idx_t = uint64_t; /* Dialogue index. */
using choice_idx_t = uint64_t; /* Choice index. */

using dialogue_map_t = std::map<dialogue_idx_t, DialogueEntry>;
using choice_map_t = std::map<choice_idx_t, std::string>;

using dialogue_iterate_t = std::function<void(const int64_t elementID, nlohmann::basic_json<>& array)>;
using dialogue_callback_t = std::function<void(const dialogue_idx_t idx, DialogueEntry& entry)>;
using choices_callback_t = std::function<void(const choice_idx_t idx, std::string& choice)>;

// ======================= S T R U C T =======================
// ===    DialogueEntry
// ======================= S T R U C T =======================

struct DialogueEntry {
    std::string m_speaker; /* Speaker. ex) Rikki Shiina */
    std::vector<DialogueSpan> m_dialogues;
};

// ======================= S T R U C T =======================
// ===    DialogueSpan
// ======================= S T R U C T =======================

struct DialogueSpan {
    std::string m_html;  /* CSS and JS.   ex) style="color: purple; font-family: 'kawaii-rikki'" onclick="..." */
    std::string m_text; /* Dialogue text. ex) Good morning, tomori-chan */

    bool operator==(const DialogueSpan&) const;
};

// ======================== C L A S S ========================
// ===    Dialogue
// ======================== C L A S S ========================

/**
 * @brief Using load, modify and save the dialogue file.
 *             (asset/json/server/scene/*.json)
 *
 * @code
 * Dialogue dialogue(...);
 *
 * if (dialogue.is_valid()) { ... }
 * @endcode
 */
class Dialogue : public IData {
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
     * @param entries Map of data to be modified.
     * @return Successfully modified choice indexes.
     */
    std::vector<choice_idx_t> update_choices(const choice_map_t& entries);

    /**
     * @brief Copy and save the data file into arg path. If file exists in target directory, overwrite it.
     *
     * @param [in] dir Target directory path.
     * @return Returns true if saved successfully.
     */
    bool backup(const path_t& dir) final;

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
     *
     * @code
     * constexpr static auto ID_ANYTHING   = ...;
     * constexpr static auto IDX_ANYTHING = ...;
     *
     * Dialogue dialogue(...);
     * dialogue.iterate_elements([&](const auto id, auto& el) {
     *      if (id != ID_ANYTHING) {
     *          break;
     *      }
     *
     *      auto& data = el[IDX_ANYTHING]; // nlohmann::json::basic_json<>&
     *      ...
     * }
     * @endcode
     */
    void iterate_elements(const dialogue_iterate_t& callback);

    /**
     * @brief Perform a for-each on the loaded dialogue data.
     *             Can get index and modify the data of spekaer and diagloue string.
     *
     * @param [in, out, optional] callback Retrieve or modify the data of spekaer and diagloue string.
     *
     * @code
     * Dialogue dialogue(...);
     * dialogue_map_t map { };
     *
     * dialogue.find_dialogues([&](const dialogue_idx_t idx, DialogueEntry& ety) {
     *      auto& spk = ety.m_speaker;
     *      auto& dia = ety.m_dialogues[0].m_text;
     *
     *      if (spk == "rikki") {
     *          dia = "I'm a rikki, I will dead :c";
     *      }
     *
     *      map[spk] = ety.m_dialogues[0];
     * });
     * @endcode
     */
    void find_dialogues(const dialogue_callback_t& callback);

    /**
     * @brief Perfomr a for-each on the loaded choice data.
     *             Can get index and modify the data of choice string.
     *
     * @param [in, out, optional] callback Retrieve or modify the data of choice string.
     *
     * @code
     * Dialogue dialogue(...);
     * std::vector<std::string> choices { };
     *
     * dialogue.find_choices([&](const choice_idx_t idx, std::string& cho) {
     *      choices.emplace_back(cho);
     *      ...
     * });
     */
    void find_choices(const choices_callback_t& callback);
public:
    /**
     * @brief Load dialogue from game data file.
     *
     * @param [in] file 'asset/json/server/scene/*.json' file path.
     */
    explicit Dialogue(const path_t& file);
private:
    path_t m_file;          /* Target dialogue in game file path */
    nlohmann::json m_j; /* Loaded dialogue data */
};


#endif //RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_HPP
