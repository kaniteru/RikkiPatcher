#ifndef DIALOGUE_MIGR_STREAM_HPP
#define DIALOGUE_MIGR_STREAM_HPP
#include "precompiled.hpp"
#include "i_stream.hpp"
#include "rikki/data/dialogue.hpp"

/*dialogue_migr_stream.hpp
 * Included classes:
 *     - DialogueMigrStream
 *     - ChoiceMigrStream
 */

// ======================== C L A S S ========================
// ===    DialogueMigrStream
// ======================== C L A S S ========================

class DialogueMigrStream : public IMigrStream {
public:
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
     * @brief Save migration data files.
     *             Game data must be unmodified.
     *
     * @param [in] dir Path to save the migration data files.
     * @return
     */
    static void save_migration_data(const path_t& dir);

public:
    /**
     * @brief Load migration data from file.
     *
     * @param [in] file Migration data file path.
     */
    explicit DialogueMigrStream(const path_t& file);
private:
    nlohmann::ordered_json m_j;

    constexpr static auto KEY_HASH = "hash";
    constexpr static auto KEY_LIST = "list";
    constexpr static auto KEY_SPEAKER    = "speaker";
    constexpr static auto KEY_DIALOGUE = "dialogue";

    friend class DialoguePatcher;
};

// ======================== C L A S S ========================
// ===    ChoiceMigrStream
// ======================== C L A S S ========================

class ChoiceMigrStream : public IMigrStream {
public:
    /**
     * @brief Get pure dialogue file hash. (because choices included dialogue file)
     *
     * @return Returns pure dialogue file hash.
     */
    std::string get_file_hash() const;

    /**
     * @brief Get pure choice entries.
     *
     * @return Returns pure choice entries.
     */
    choice_map_t get_choices() const;

    /**
     * @brief Save migration data files.
     *             Game data must be unmodified.
     *
     * @param [in] dir Path to save the migration data files.
     * @return
     */
    static void save_migration_data(const path_t& dir);

public:
    explicit ChoiceMigrStream(const path_t& file);
private:
    nlohmann::ordered_json m_j;

    constexpr static auto KEY_HASH = "hash";
    constexpr static auto KEY_LIST = "list";
};


#endif //DIALOGUE_MIGR_STREAM_HPP
