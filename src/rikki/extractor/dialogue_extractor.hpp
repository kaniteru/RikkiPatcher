#ifndef RIKKI_PATCHER_RIKKI_EXTRACTOR_DIALOGUE_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_EXTRACTOR_DIALOGUE_EXTRACTOR_HPP
#include "precompiled.hpp"
#include "i_extractor.hpp"

/* dialogue_extractor.hpp
 *  Included classes:
 *      - DialogueExtractor
 *      - ChoiceExtractor
 */

// ======================== C L A S S ========================
// ===    DialogueExtractor
// ======================== C L A S S ========================

class DialogueExtractor final : public IExtractor {
public:
    /**
     * @brief Extract game dialogues data and convert it custom dialogue data structure.
     *
     * @return Returns extracted files count.
     */
    size_t extract() final;

public:
    /**
     * @brief Initialize using target data folder.
     *
     * @param [in] dst Target data root folder path.
     */
    explicit DialogueExtractor(const path_t& dst);
private:
    path_t m_db; /* Using save the dialogue data path */

    constexpr static auto FOLDER_BASE = "dialogues";
};

// ======================== C L A S S ========================
// ===    ChoiceExtractor
// ======================== C L A S S ========================

class ChoiceExtractor final : public IExtractor {
public:
    /**
     * @brief Extract game choices data and convert it custom choice data structure.
     *
     * @return Returns extracted files count.
     */
    size_t extract() final;

public:
    /**
     * @brief Initialize using target data folder.
     *
     * @param [in] dst Target data root folder path.
     */
    explicit ChoiceExtractor(const path_t& dst);
private:
    path_t m_dataBase; /* Using save the choice data path */

    constexpr static auto FOLDER_BASE = "choices";
};


#endif //RIKKI_PATCHER_RIKKI_EXTRACTOR_DIALOGUE_EXTRACTOR_HPP
