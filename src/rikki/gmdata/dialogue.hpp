#ifndef RIKKI_PATCHER_RIKKI_DIALOGUE_HPP
#define RIKKI_PATCHER_RIKKI_DIALOGUE_HPP
#include "precompiled.hpp"

using tran_speakers_t = std::unordered_map<std::string, std::string>;
using tran_dialogues_t = std::vector<std::string>;
using dialogue_callback_t = std::function<void(std::string& speaker, std::string&)>;

struct DialogueEntry {
    tran_speakers_t m_speakers; // org - translated
    tran_dialogues_t m_dialogues;
};

class Dialogue {
public:
    bool is_valid() const;

    DialogueEntry extract();
    void update(DialogueEntry& de);

    bool save();
    bool save(const path_t& path);
private:
    void find_dialogue(const dialogue_callback_t& callback);

public:
    explicit Dialogue(const path_t& file);
private:
    bool m_isValid;
    nlohmann::json m_j;
    path_t m_file;
};


#endif //RIKKI_PATCHER_RIKKI_DIALOGUE_HPP
