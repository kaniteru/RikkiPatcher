#include "dialogue_extractor.hpp"
#include "dialogue_patcher.hpp"
#include "utils/instance_factory.hpp"
#include "utils/filesystem_util.hpp"
#include "rikki/dir_mgr.hpp"
#include "wv/enums.hpp"
#include "wv/wv_invoker.hpp"

size_t DialogueExtractor::extract() {
    const auto gmdir = InstanceFactory::instance().get<DirMgr>()->get(DIR_GAME_JSON_DIALOGUES);

    size_t total = 0;
    size_t failed = 0;
    size_t ok = 0;

    for (const auto& files = FilesystemUtil::sort_files(gmdir); const auto& f : files) {
        const auto fName = f.filename().generic_u8string();
        auto log = fName + std::u8string(u8" => ");

        total++;

        Dialogue pureDia(f);

        if (!pureDia.is_valid()) {
            log += u8"Read failed";
            WvInvoker::log(LOG_LV_PROG, log);

            failed++;
            continue;
        }

        auto dialogues = pureDia.extract();

        if (dialogues.empty()) {
            log += u8"Pass (no data)";
            WvInvoker::log(LOG_LV_PROG, log);

            continue;
        }

        DialoguePatchStream patchStream(path_t(m_dataBase).append(fName));
        patchStream.set_dialogues(dialogues);

        if (patchStream.save()) {
            ok++;
            log += u8"OK";
        } else {
            failed++;
            log += u8"Write failed";
        }

        WvInvoker::log(LOG_LV_PROG, log);
    }

    const auto log = "Total: " + std::to_string(total) + " | extracted: " + std::to_string(ok) + " | Failed: " + std::to_string(failed);
    WvInvoker::log(LOG_LV_INFO, log);
    return ok;
}

DialogueExtractor::DialogueExtractor(const path_t& dst) :
    IExtractor(dst) {

    m_dataBase = path_t(dst).append(FOLDER_BASE);
    std::filesystem::create_directories(m_dataBase);

    m_isAvailable = true;
}
