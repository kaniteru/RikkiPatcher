#include "ui_text_in_game_key.hpp"

const InGameUITextKey InGameUITextKeyMgr::previous_dialogue = {
    "asset/json/server/ui/sui3.json",
    "88195832281_0.5124109114928297",
    "49888868392_0.20897767076252083",
    "51002554449_0.9381395484044113"
};

const InGameUITextKey InGameUITextKeyMgr::hide_interface = {
    "asset/json/server/ui/sui3.json",
    "76984664881_0.08983806891086643",
    "49888868392_0.20897767076252083",
    "51002554449_0.9381395484044113"
};

const InGameUITextKey InGameUITextKeyMgr::auto_play_dialogue = {
    "asset/json/server/ui/sui3.json",
    "76984799489_0.0026219008822241374",
    "49888868392_0.20897767076252083",
    "51002554449_0.9381395484044113"
};

const InGameUITextKey InGameUITextKeyMgr::auto_skip_dialogue = {
    "asset/json/server/ui/sui3.json",
    "76984803161_0.03457308488415656",
    "49888868392_0.20897767076252083",
    "51002554449_0.9381395484044113"
};

const InGameUITextKey InGameUITextKeyMgr::save_game_progress = {
    "asset/json/server/ui/sui3.json",
    "76984806113_0.5374903177643624",
    "49888868392_0.20897767076252083",
    "51002554449_0.9381395484044113"
};

const InGameUITextKey InGameUITextKeyMgr::load_game_progress = {
    "asset/json/server/ui/sui3.json",
    "76984808631_0.35458940356223123",
    "49888868392_0.20897767076252083",
    "51002554449_0.9381395484044113"
};

const InGameUITextKey InGameUITextKeyMgr::settings = {
    "asset/json/server/ui/sui3.json",
    "76984817433_0.9865774889265957",
    "49888868392_0.20897767076252083",
    "51002554449_0.9381395484044113"
};

const InGameUITextKey InGameUITextKeyMgr::return_to_title = {
    "asset/json/server/ui/sui3.json",
    "76984820425_0.7246081356121747",
    "49888868392_0.20897767076252083",
    "51002554449_0.9381395484044113"
};

const InGameUITextKey InGameUITextKeyMgr::enter_save_file_name = {
    "asset/json/server/ui/sui7.json",
    "42750672835_0.9916632150539608",
    "49888868392_0.20897767076252083",
    "42750648781_0.6423333117128123"
};

const InGameUITextKey InGameUITextKeyMgr::enter_save_file_name2 = {
    "asset/json/server/ui/sui7.json",
    "172567439862_0.37944645234487706",
    "49888868392_0.20897767076252083",
    "42750648781_0.6423333117128123"
};

const std::map<const char*, const InGameUITextKey&> InGameUITextKeyMgr::g_keys = {
    { KEY_PREVIOUS_DIALOGUE, previous_dialogue },
    { KEY_HIDE_INTERFACE, hide_interface },
    { KEY_AUTO_PLAY_DIALOGUE, auto_play_dialogue },
    { KEY_AUTO_SKIP_DIALOGUE, auto_skip_dialogue },
    { KEY_SAVE_GAME_PROGRESS, save_game_progress },
    { KEY_LOAD_GAME_PROGRESS, load_game_progress },
    { KEY_SETTINGS, settings },
    { KEY_RETURN_TO_TITLE, return_to_title },
    { KEY_ENTER_SAVE_FILE_NAME, enter_save_file_name }
};