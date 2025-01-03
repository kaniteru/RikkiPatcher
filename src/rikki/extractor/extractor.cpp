#include "extractor.hpp"
#include "rikki/extractor/dialogue/dialogue_extractor.hpp"
#include "ui/ui_extractor.hpp"
#include "rikki/extractor/copy/copy_extractor.hpp"
#include "rikki/patcher/dialogue/dialogue_patcher.hpp"
#include "rikki/patcher/ui/ui_patcher.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    Extractor
// ======================== C L A S S ========================

void Extractor::do_extract(const path_t& dst) {
    constexpr auto extract_process = [&](IExtractor* p, const std::string& str) {
        WvInvoker::log(LOG_LV_ALERT, "Start extract " + str + " data from game");
        p->extract();
        WvInvoker::log(LOG_LV_ALERT, "Finished extract the " + str + " data from game");
    };

     // start extract data
    WvInvoker::log(LOG_LV_ALERT, "Start extract data from game");

    // extract dialogues
    DialogueExtractor diaExtractor(dst);
    extract_process(&diaExtractor, "dialogues");

    // extract choices
    ChoiceExtractor choExtractor(dst);
    extract_process(&choExtractor, "choices");

    // extract ui
    UIExtractor uiExtractor(dst);
    extract_process(&uiExtractor, "ui");

    // extract copy
    CopyExtractor cpyExtractor(dst);
    extract_process(&cpyExtractor, "copy");

    // finished extract data
    WvInvoker::log(LOG_LV_ALERT, "Finished extract data from game");
}

void Extractor::do_generate_migration_info(const path_t& dst) {
    constexpr auto generate_process = [&](IPatcher* p, const std::string& str) {
        if (!p->is_available()) {
            WvInvoker::log(LOG_LV_ERR, "Can't generate the " + str + " migration data");
            return false;
        }

        WvInvoker::log(LOG_LV_ALERT, "Start generate the " + str + " migration data");
        p->generate_migration_info();
        WvInvoker::log(LOG_LV_ALERT, "Finished generate the " + str + " migration data");
        return true;
    };

    // start generate migration info
    WvInvoker::log(LOG_LV_ALERT, "Start generate the migration info");

    // generate dialogue migration info
    DialoguePatcher diaPatcher(dst);
    generate_process(&diaPatcher, "dialogues");

    // generate choice migration info
    ChoicePatcher choPatcher(dst);
    generate_process(&choPatcher, "choices");

    // generate ui migration info
    UIPatcher uiPatcher(dst);
    generate_process(&uiPatcher, "ui");
    uiPatcher.close();

    // finished generate migration info
    WvInvoker::log(LOG_LV_ALERT, "Finished generate the migration info");
}
