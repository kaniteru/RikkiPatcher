#ifndef RIKKI_PATCHER_RIKKI_EXTRACTOR_DIALOGUE_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_EXTRACTOR_DIALOGUE_EXTRACTOR_HPP
#include "precompiled.hpp"
#include "rikki/extractor/i_extractor.hpp"

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
     * @param [in] dst Path of target patch data folder.
     */
    explicit DialogueExtractor(const path_t& dst);
private:
    const path_t m_db; /* Path of patch data folder */
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
     * @param [in] dst Path of target patch data folder.
     */
    explicit ChoiceExtractor(const path_t& dst);
private:
    const path_t m_db; /* Path of patch data folder */
};


#endif //RIKKI_PATCHER_RIKKI_EXTRACTOR_DIALOGUE_EXTRACTOR_HPP
