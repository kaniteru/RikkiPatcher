#include "dialogue_patch_helper.hpp"
#include "rikki/data/dialogue/i_dialogue.hpp"
#include "rikki/data/dialogue/dialogue_json.hpp"
#include "rikki/stream/dialogue_patch_stream.hpp"

// ======================== C L A S S ========================
// ===    DialoguePatchHelper
// ======================== C L A S S ========================

PatcherResult DialoguePatchHelper::do_patch(const path_t& fPatch, IDialogue* const pDst) {
    PatcherResult result { };
    size_t& total   =  result.m_total;
    size_t& ok       = result.m_ok;

    const DialoguePatchStream stream(fPatch);
    const auto map = stream.get_dialogues();
    const auto lenPatched = pDst->update_dialogues(map);

    total += map.size();
    ok     += lenPatched.size();
    return result;
}

PatcherResult DialoguePatchHelper::do_migrate(const path_t& fPatch, const path_t& fMigr, const dialogue_map_t& pureMap) {
    PatcherResult result { };
    size_t& total   =  result.m_total;

    if (pureMap.empty()) {
        if (std::filesystem::exists(fPatch)) {
            std::filesystem::remove(fPatch);
        }

        return DialoguePatchHelperResult::_OK_NO_DATA;
    }

    DialoguePatchStream patchStream(fPatch);
    const auto patchMap = patchStream.get_dialogues();

    if (!std::filesystem::exists(fPatch) || !std::filesystem::exists(fMigr)) {
        patchStream.clear();
        patchStream.set_dialogues(pureMap);

        std::filesystem::create_directories(path_t(fPatch).parent_path());

        if (!patchStream.save()) {
            return DialoguePatchHelperResult::_FAILED_SAVE;
        }

        const auto size = pureMap.size();
        return { size, size, 0, 0 };
    }

    const DialoguePatchStream migrStream(fMigr);
    const auto migrMap = migrStream.get_dialogues();

    dialogue_map_t newMap { };

    for (const auto& [idx, pureEntry] : pureMap) {
        total++;

        if (const auto migrIt = migrMap.find(idx); migrIt != migrMap.end()) {
            const auto& migrEntry = migrIt->second;

            // check is equals the pure-entry same as migr-entry
            if (pureEntry == migrEntry) {
                // found translated entry
                if (const auto patchIt = patchMap.find(idx); patchIt != patchMap.end()) {
                    newMap[idx] = patchIt->second;
                    continue;
                }
            }
        }

            // dialogue was updated
            j::Dialogue newEntry = pureEntry;
            bool foundSpk = false;
            const auto lenPureSpans = pureEntry.spans.size();
            std::vector<size_t> foundTexts { };
            foundTexts.reserve(lenPureSpans);

            // check is atts updated
            if (migrMap.at(idx).atts == pureEntry.atts) {
                newEntry.atts = patchMap.at(idx).atts;
            }

            for (const auto& [migrIdx, migrEntry] : migrMap) {
                // check is equals the migr-entry same as pure-entry
                if (migrEntry == pureEntry) {
                    // translated entry found
                    newEntry = patchMap.at(migrIdx);
                    break;
                }

                // found a translated speaker when not found
                if (!foundSpk && migrEntry.speaker == pureEntry.speaker) {
                    newEntry.speaker = patchMap.at(migrIdx).speaker;
                    foundSpk = true;
                }

                // found translated texts when not found
                if (!foundTexts.size() != lenPureSpans) {
                    for (uint32_t i = 0; i < pureEntry.spans.size(); i++) {
                        if (std::ranges::find(foundTexts, i) != foundTexts.end()) {
                            continue;
                        }

                        const auto& pureText = pureEntry.spans[i].html;
                        const auto& migrSpans = migrEntry.spans;

                        for (uint32_t j = 0; j < migrSpans.size(); j++) {
                            if (migrSpans[j].text == pureText) {
                                foundTexts.push_back(i);
                                newEntry.spans[i].text = patchMap.at(migrIdx).spans[j].text;
                                break;
                            }
                        }
                    }
                }

                // escape the loop when found translated entry perfectly
                if (foundSpk && foundTexts.size() == lenPureSpans) {
                    break;
                }
            }

            newMap[idx] = newEntry;
    }

    patchStream.clear();
    patchStream.set_dialogues(newMap);

    if (!patchStream.save()) {
        return DialoguePatchHelperResult::_FAILED_SAVE;
    }

    return result;
}

// ======================== C L A S S ========================
// ===    ChoicePatchHelper
// ======================== C L A S S ========================

PatcherResult ChoicePatchHelper::do_patch(const path_t& fPatch, IDialogue* const pDst) {
    PatcherResult result { };
    size_t& total   =  result.m_total;
    size_t& ok       = result.m_ok;

    const ChoicePatchStream stream(fPatch);
    const auto map = stream.get_choices();
    const auto lenPatched = pDst->update_choices(map);

    total += map.size();
    ok     += lenPatched.size();
    return result;
}

PatcherResult ChoicePatchHelper::do_migrate(const path_t& fPatch, const path_t& fMigr, const choice_map_t& pureMap) {
    PatcherResult result { };
    size_t& total   =  result.m_total;
    size_t& ok       = result.m_ok;
    size_t& failed  = result.m_failed;

    if (pureMap.empty()) {
        if (std::filesystem::exists(fPatch)) {
            std::filesystem::remove(fPatch);
        }

        return DialoguePatchHelperResult::_OK_NO_DATA;
    }

    ChoicePatchStream patchStream(fPatch);
    const auto patchMap = patchStream.get_choices();

    if (!std::filesystem::exists(fPatch) || !std::filesystem::exists(fMigr)) {
        patchStream.clear();
        patchStream.set_choices(pureMap);

        std::filesystem::create_directories(path_t(fPatch).parent_path());

        if (!patchStream.save()) {
            return DialoguePatchHelperResult::_FAILED_SAVE;
        }

        const auto size = pureMap.size();
        return { size, size, 0, 0 };
    }

    const ChoicePatchStream migrStream(fMigr);
    const auto migrMap = migrStream.get_choices();

    choice_map_t newMap { };

    for (const auto& [idx, pureEntry] : pureMap) {
        if (const auto migrIt = migrMap.find(idx); migrIt != migrMap.end()) {
            const auto& migrEntry = migrIt->second;

            // check is equals the pure-entry same as migr-entry
            if (pureEntry == migrEntry) {
                // found translated entry
                if (const auto patchIt = patchMap.find(idx); patchIt != patchMap.end()) {
                    newMap[idx] = patchIt->second;
                    continue;
                }
            }
        }

        // choice was updated
        j::Choice newEntry = pureEntry;

        for (const auto& [migrIdx, migrEntry] : migrMap) {
            // check is equals the migr-entry same as pure-entry
            if (migrEntry == pureEntry) {
                // translated entry found
                newEntry = patchMap.at(migrIdx);
                break;
            }
        }

        newMap[idx] = newEntry;
    }

    patchStream.clear();
    patchStream.set_choices(newMap);

    if (!patchStream.save()) {
        return DialoguePatchHelperResult::_FAILED_SAVE;
    }

    return result;
}
