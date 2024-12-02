#ifndef RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_HPP
#define RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_HPP
#include "precompiled.hpp"
#include "i_data.hpp"

struct DialogueEntry;

using dialogue_idx_t = uint64_t; /* Dialogue index. */
using dialogue_map_t = std::map<dialogue_idx_t, DialogueEntry>;
using speaker_map_t = std::map<std::string, std::string>; // chinense | translated
using dialogue_callback_t = std::function<void(dialogue_idx_t idx, std::string& speaker, std::string&)>;

struct DialogueEntry {
    std::string m_speaker; /* Speaker. ex) Rikky Shiina */
    std::string m_dialogue; /* Dialogue. ex) Good morning, tomori-chan */
};

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
     * @brief Check is dialogue data loaded successfully.
     *
     * @return Returns true if data loaded successfully.
     */
    bool is_valid() final;

    /**
     * @brief Extract all existing dialogues from data.
     *
     * @return Existing dialogues data map.
     */
    dialogue_map_t extract();

    /**
     * @brief Modify the dialogues data.
     *
     * @param [in] entries Map of data to be modified.
     * @return Successfully modified dialogue indexes.
     */
    std::vector<dialogue_idx_t> update(const dialogue_map_t& entries);

    /**
     * @brief Copy and save the data file into arg path.
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
     * @brief Perform a for-each on the loaded dialogue data.
     *             Can get index and modify the data of spekaer and diagloue string.
     *
     * @param [in, out, optional] callback Retrieve or modify the data of spekaer and diagloue string.
     *
     * @code
     * Dialogue dialogue(...);
     * std::vector<std::string> speakers  { };
     * std::vector<std::string> dialogues { };
     *
     * dialogue.find_dialogue([&](dialogue_idx_t idx, std::string& spk, std::string& dia) {
     *      speakers.emplace_back(spk);
     *      dialogues.emplace_back(dia);
     *
     *      if (spk == "rikki") {
     *          dia = "I'm a rikki, I will dead :c";
     *      }
     * });
     * @endcode
     */
    void find_dialogue(const dialogue_callback_t& callback);

public:
    /**
     * @brief Load dialogue from game data file.
     *
     * @param [in] file asset/json/server/scene/*.json file path.
     */
    explicit Dialogue(const path_t& file);
private:
    bool m_isValid;         /* Using is dialogue data loaded successful in constructor. */
    path_t m_file;          /* Target dialogue in game file path */
    nlohmann::json m_j; /* Loaded dialogue data */
};

struct DialogueMigr {
    std::string m_hash;
    dialogue_map_t m_entries;

    bool save(const path_t& file) const;

    static DialogueMigr from_file(const path_t& file);
private:
    constexpr static auto KEY_MIGR_HASH         = "hash";
    constexpr static auto KEY_MIGR_DIA_LIST  = "dia_list";
    constexpr static auto KEY_MIGR_SPEAKER    = "speaker";
    constexpr static auto KEY_MIGR_DIALOGUE = "dialogue";
};


#endif //RIKKI_PATCHER_RIKKI_DATA_DIALOGUE_HPP
