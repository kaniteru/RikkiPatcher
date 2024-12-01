#ifndef RIKKI_PATCHER_RIKKI_PATCHER_HPP
#define RIKKI_PATCHER_RIKKI_PATCHER_HPP
#include "precompiled.hpp"

class IPatcher {
protected:
    constexpr static auto FILE_SPEAKERS = "speakers.json";
    constexpr static auto FILE_DIALOGUES = "dialogues.txt";
};

class Extractor : IPatcher {
public:
    static void extract_dialogues(const path_t& src, const path_t& dst);
};

class Patcher : IPatcher {
public:
    static void load_and_patch(const path_t& src);
    static void migration_modified_data(const path_t& src);
private:
    static void update_dialogues(const path_t& spk, const path_t& dia, const path_t& dst);
};


#endif //RIKKI_PATCHER_RIKKI_PATCHER_HPP
