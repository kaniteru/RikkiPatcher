#ifndef RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_EXTRACTOR_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_EXTRACTOR_HPP
#include "precompiled.hpp"
#include "i_extractor.hpp"

class DialogueExtractor : public IExtractor {
public:
    /**
     * @brief Extract game dialogues data and convert it custom dialogue data structure.
     *
     * @return Returns extracted files count.
     */
    size_t extract() final;

public:
    explicit DialogueExtractor(const path_t& dst);
private:
    path_t m_dataBase;

    constexpr static auto FOLDER_BASE = "dialogues";
};



#endif //RIKKI_PATCHER_RIKKI_PATCHER_DIALOGUE_EXTRACTOR_HPP
