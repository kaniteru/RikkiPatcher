#ifndef RIKKI_PATCHER_WV_WV_BINDER_HPP
#define RIKKI_PATCHER_WV_WV_BINDER_HPP
#include "precompiled.hpp"

#define HANDLER_ARGS                const std::string& args
#define ASYNC_HANDLER_ARGS const std::string& id, const std::string& args, void* pArgs

class WvBinder {
public:
    void bind();

private:
    std::string init_patcher(HANDLER_ARGS);
    std::string request_trans(HANDLER_ARGS);
    std::string open_github(HANDLER_ARGS);
    std::string open_project_web(HANDLER_ARGS);

    std::string set_gmdir_manually(HANDLER_ARGS);
    std::string set_gmdir_automatically(HANDLER_ARGS);

    std::string select_patch_data_dir(HANDLER_ARGS);

    std::string patch_extract(HANDLER_ARGS);
    std::string patch_apply(HANDLER_ARGS);
    std::string migrate_patch_data(HANDLER_ARGS);
};


#endif //RIKKI_PATCHER_WV_WV_BINDER_HPP
