#include "patcher.hpp"
#include "rikki/patcher/dialogue/dialogue_patcher.hpp"
#include "ui/ui_patcher.hpp"
#include "rikki/patcher/copy/copy_patcher.hpp"

#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

// ======================== C L A S S ========================
// ===    Patcher
// ======================== C L A S S ========================

void Patcher::do_patch(const path_t& src) {
    // start apply custom data
    WvInvoker::log(LOG_LV_ALERT, "Start apply custom patch data into game");

    // apply dialogues
    WvInvoker::log(LOG_LV_ALERT, "Start apply custom dialogues data into game");
    DialoguePatcher diaPatcher(src);
    diaPatcher.patch();
    WvInvoker::log(LOG_LV_ALERT, "Finished apply custom dialogues data into game");

    // apply choices
    WvInvoker::log(LOG_LV_ALERT, "Start apply custom choices data into game");
    ChoicePatcher choPatcher(src);
    choPatcher.patch();
    WvInvoker::log(LOG_LV_ALERT, "Finished apply custom choices data into game");

    // apply ui-texts
    WvInvoker::log(LOG_LV_ALERT, "Start apply custom ui data into game");
    UIPatcher uiPatcher(src);
    uiPatcher.patch();
    uiPatcher.close();
    WvInvoker::log(LOG_LV_ALERT, "Finished apply custom ui data into game");

    // apply copy patches
    WvInvoker::log(LOG_LV_ALERT, "Start apply custom copy data into game");
    CopyPatcher cpyPatcher(src);
    cpyPatcher.patch();
    WvInvoker::log(LOG_LV_ALERT, "Finished apply custom copy data into game");

    // finished
    WvInvoker::log(LOG_LV_ALERT, "Finished apply custom patch data into game");
}

void Patcher::do_migration(const path_t& dir) {
    constexpr auto migrate_process = [&](IPatcher* p, const std::string& str) {
        if (!p->is_available()) {
            WvInvoker::log(LOG_LV_ERR, "Can't migrate the " + str + " data");
            return false;
        }

        WvInvoker::log(LOG_LV_ALERT, "Start the migration of " + str + " data");
        p->migration();
        p->generate_migration_info();
        WvInvoker::log(LOG_LV_ALERT, "Finished the migration of " + str + " data");
        return true;
    };

    // start migrate custom data
    WvInvoker::log(LOG_LV_ALERT, "Start the migration of custom data");

    // migrate dialogues data
    DialoguePatcher diaPatcher(dir);
    migrate_process(&diaPatcher, "dialogues");

    // migrate choices data
    ChoicePatcher choPatcher(dir);
    migrate_process(&choPatcher, "choices");

    // migrate ui data
    UIPatcher uiPatcher(dir);
    migrate_process(&uiPatcher, "ui");
    uiPatcher.close();

    WvInvoker::log(LOG_LV_INFO, "Currently, copy patch doesn't support the migration");

    // finished
    WvInvoker::log(LOG_LV_ALERT, "Finished the migration of custom data");
}
