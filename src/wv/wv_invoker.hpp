#ifndef RIKKI_PATCHER_WV_WV_INVOKER_HPP
#define RIKKI_PATCHER_WV_WV_INVOKER_HPP
#include "precompiled.hpp"
#include "wv_mgr.hpp"
#include "wv_args_parser.hpp"

#include "utils/logger.hpp"
#include "utils/string_util.hpp"

enum eWvLogLv {
    WV_LOG_LV_INFO   = 0,
    WV_LOG_LV_ALERT  = 1,
    WV_LOG_LV_PROG    = 2,
    WV_LOG_LV_FATAL = 3,
    WV_LOG_LV_DEBUG = 4
};

// ======================== C L A S S ========================
// ===    WvInvoker
// ======================== C L A S S ========================

class WvInvoker {
public:
    template<typename... Args>
    static webview::noresult call(std::string_view func, Args&&... args);

    static void init_success();

    static void init_gmdir(const path_t& gmdir);

    static void selected_patch_data_dir(const path_t& dir);

    static void finish_patch();

    template <typename... Args>
    static void log(eWvLogLv lv, std::string_view fmt, Args&&... args);

    template <typename... Args>
    static void log(eWvLogLv lv, std::u8string_view fmt, Args&&... args);

    static void clear_log();
};

template<typename... Args>
webview::noresult WvInvoker::call(const std::string_view func, Args&&... args) {
    const WvArgsParser parser(args...);
    const std::string cmd = std::string(func) + "(" + parser.get() + ");";
    const auto u8cmd = StringUtil::str_to_u8(cmd);
    const auto js = StringUtil::u8_to_cstr(u8cmd);
    DLOG("execute js: {}", cmd);
    return WvMgr::get()->eval(js);
}

template<typename ... Args>
void WvInvoker::log(eWvLogLv lv, std::string_view fmt, Args&&... args) {
    constexpr static auto FN = "_log";

    std::string msg { };

    if constexpr (sizeof...(Args) > 0) {
        msg = std::format(fmt, std::forward<Args>(args)...);
    } else {
        msg = fmt;
    }

    WvInvoker::call(FN, lv, msg);
}

template <>
struct std::formatter<std::u8string> {
    constexpr auto parse(std::format_parse_context& ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const std::u8string& u8str, FormatContext& ctx) const -> decltype(ctx.out()) {
        return std::format_to(ctx.out(), "{}", std::string(u8str.begin(), u8str.end()));
    }
};


template<typename ... Args>
void WvInvoker::log(eWvLogLv lv, std::u8string_view fmtt, Args&&... args) {
    constexpr static auto FN = "_log";
    std::u8string fmt(fmtt.begin(), fmtt.end());
    // Create a format string
    std::basic_format_args format_args = std::make_format_args(args...);

    // Use std::vformat with the u8string and the format arguments
    std::string temp = std::vformat(std::string(fmt.begin(), fmt.end()), format_args);
    std::u8string msg(temp.begin(), temp.end());
    WvInvoker::call(FN, lv, StringUtil::u8_to_cstr(msg));
}

// ======================= S T R U C T =======================
// ===    WvLogFmt
// ======================= S T R U C T =======================

struct WvLogFmt {
    // wv invoker
    static constexpr auto WV_INVOKER_SET_GM_DIR = u8"wv.invoker.set.game_directory"; // game directory set: {}

    // wv binder
    static constexpr auto WV_BINDER_INIT_START = u8"wv.binder.init.start"; // Initializing patcher...
    static constexpr auto WV_BINDER_INIT_SUCCESS = u8"wv.binder.init.success"; // init success
    static constexpr auto WV_BINDER_DIALOG_FAILED = u8"wv.binder.dialog.failed"; // An error occurred while retrieving the path
    static constexpr auto WV_BINDER_DIALOG_GMDIR_NOTICE = u8"wv.binder.dialog.gmdir.notice"; //Please select the folder containing the game executable (.exe) file
    static constexpr auto WV_BINDER_GMDIR_AUTO_FAILED_FIND_STEAM = u8"wv.binder.gmdir.auto.failed.find_steam"; // Can't find steam
    static constexpr auto WV_BINDER_GMDIR_AUTO_FAILED_FIND_GAME_FROM_STEAM = u8"wv.binder.gmdir.auto.failed.find_game_from_steam"; // Can't find installed game in steam
    static constexpr auto WV_BINDER_GMDIR_AUTO_FAILED_GAME_NOT_INSTALLED = u8"wv.binder.gmdir.auto.failed.game_not_installed"; // Game doesn't installed
    static constexpr auto WV_BINDER_GMDIR_AUTO_FAILED_FIND_GAME_NAME = u8"wv.binder.gmdir.auto.failed.find_game_name"; //Can't find installed game name
    static constexpr auto WV_BINDER_GMDIR_AUTO_FAILED_GAME_DIR_NOT_EXISTS = u8"wv.binder.gmdir.auto.failed.game_dir_not_exists"; // Game directory doesn't exists.
    static constexpr auto WV_BINDER_GMDIR_AUTO_OK_STEAM_DIR = u8"wv.binder.gmdir.auto.ok.steam_dir"; // fount steam directory: {}
    static constexpr auto WV_BINDER_GMDIR_AUTO_OK_GAME_INSTALLED = u8"wv.binder.gmdir.auto.ok.game_installed"; // Checked game installed
    static constexpr auto WV_BINDER_GMDIR_AUTO_OK_GAME_NAME = u8"wv.binder.gmdir.auto.ok.game_name"; // Checked game folder name
    static constexpr auto WV_BINDER_GMDIR_AUTO_OK_GAME_DIR = u8"wv.binder.gmdir.auto.ok.game_directory"; // Found game directory
    static constexpr auto WV_BINDER_EXTRACT_RESULT = u8"wv.binder.extract.result"; // You can find extracted data into: {}

    // dialogue
    static constexpr auto PATCH_DIALOGUE_START = u8"patch.dialogue.start";
    static constexpr auto PATCH_DIALOGUE_PASS_NO_GM_DATA = u8"patch.dialogue.pass.no_gm_data";
    static constexpr auto PATCH_DIALOGUE_FAILED_READ = u8"patch.dialogue.failed.read";
    static constexpr auto PATCH_DIALOGUE_FAILED_WRITE = u8"patch.dialogue.failed.write";
    static constexpr auto PATCH_DIALOGUE_OK = u8"patch.dialogue.ok";
    static constexpr auto PATCH_DIALOGUE_RESULT = u8"patch.dialogue.result";

    static constexpr auto MIGR_DIALOGUE_START = u8"patch.dialogue.start";
    static constexpr auto MIGR_DIALOGUE_FAILED_READ = u8"migration.dialogue.failed.read";
    static constexpr auto MIGR_DIALOGUE_FAILED_WRITE = u8"migration.dialogue.failed.write";
    static constexpr auto MIGR_DIALOGUE_OK_NO_GM_DATA = u8"migration.dialogue.pass.no_gm_data";
    static constexpr auto MIGR_DIALOGUE_OK = u8"migration.dialogue.ok";
    static constexpr auto MIGR_DIALOGUE_RESULT = u8"migration.dialogue.result";
    static constexpr auto MIGR_DIALOGUE_EXTRACT = u8"migration.dialogue.extract";

    static constexpr auto EXTRACT_DIALOGUE_START = u8"patch.dialogue.start";
    static constexpr auto EXTRACT_DIALOGUE_PASS_NO_GM_DATA = u8"extract.dialogue.pass.no_gm_data";
    static constexpr auto EXTRACT_DIALOGUE_FAILED_READ = u8"extract.dialogue.failed.read";
    static constexpr auto EXTRACT_DIALOGUE_FAILED_WRITE = u8"extract.dialogue.failed.write";
    static constexpr auto EXTRACT_DIALOGUE_OK = u8"extract.dialogue.ok";
    static constexpr auto EXTRACT_DIALOGUE_RESULT = u8"extract.dialogue.result";

    // choice
    static constexpr auto PATCH_CHOICE_START = u8"patch.choice.start";
    static constexpr auto PATCH_CHOICE_PASS_NO_GM_DATA = u8"patch.choice.pass.no_gm_data";
    static constexpr auto PATCH_CHOICE_FAILED_READ = u8"patch.choice.failed.read";
    static constexpr auto PATCH_CHOICE_FAILED_WRITE = u8"patch.choice.failed.write";
    static constexpr auto PATCH_CHOICE_OK = u8"patch.choice.ok";
    static constexpr auto PATCH_CHOICE_RESULT = u8"patch.choice.result";

    static constexpr auto MIGR_CHOICE_START = u8"patch.choice.start";
    static constexpr auto MIGR_CHOICE_FAILED_READ = u8"migration.choice.failed.read";
    static constexpr auto MIGR_CHOICE_FAILED_WRITE = u8"migration.choice.failed.write";
    static constexpr auto MIGR_CHOICE_OK_NO_GM_DATA = u8"migration.choice.pass.no_gm_data";
    static constexpr auto MIGR_CHOICE_OK = u8"migration.choice.ok";
    static constexpr auto MIGR_CHOICE_RESULT = u8"migration.choice.result";
    static constexpr auto MIGR_CHOICE_EXTRACT = u8"migration.choice.extract";

    static constexpr auto EXTRACT_CHOICE_START = u8"patch.choice.start";
    static constexpr auto EXTRACT_CHOICE_PASS_NO_GM_DATA = u8"extract.choice.pass.no_gm_data";
    static constexpr auto EXTRACT_CHOICE_FAILED_READ = u8"extract.choice.failed.read";
    static constexpr auto EXTRACT_CHOICE_FAILED_WRITE = u8"extract.choice.failed.write";
    static constexpr auto EXTRACT_CHOICE_OK = u8"extract.choice.ok";
    static constexpr auto EXTRACT_CHOICE_RESULT = u8"extract.choice.result";

    // copy
    static constexpr auto PATCH_COPY_START = u8"patch.copy.start";
    static constexpr auto PATCH_COPY_FAILED_READ = u8"patch.copy.failed.read";
    static constexpr auto PATCH_COPY_FAILED_EMPTY = u8"patch.copy.failed.empty";
    static constexpr auto PATCH_COPY_FAILED_EXCEPTION = u8"patch.copy.failed.exception";
    static constexpr auto PATCH_COPY_OK_FILE = u8"patch.copy.ok.file";
    static constexpr auto PATCH_COPY_OK_DIR = u8"patch.copy.ok.directory";
    static constexpr auto PATCH_COPY_RESULT = u8"patch.copy.result";

    static constexpr auto EXTRACT_COPY_START = u8"extract.copy.start";
    static constexpr auto EXTRACT_COPY_FAILED_WRITE = u8"extract.copy.failed.write";
    static constexpr auto EXTRACT_COPY_RESULT = u8"extract.copy.result";

    // ui
    static constexpr auto PATCH_UI_FAILED_COPY = u8"patch.ui.failed.copy"; // Can't copied the game file from game directory
    static constexpr auto PATCH_UI_FAILED_COPY_TO_GAME = u8"patch.ui.failed.copy.game"; // Can't copied the patched game file to game directory
    static constexpr auto PATCH_UI_FAILED_READ = u8"patch.ui.failed.read"; // Can't read the game data
    static constexpr auto PATCH_UI_FAILED_WRITE = u8"patch.ui.failed.write"; // Can't save the patched game file

    // ui-dialogue
    static constexpr auto PATCH_UI_DIALOGUE_START = u8"patch.ui_dialogue.start";
    static constexpr auto PATCH_UI_DIALOGUE_FAILED_READ = u8"patch.ui_dialogue.failed.read";
    static constexpr auto PATCH_UI_DIALOGUE_OK = u8"patch.ui_dialogue.ok";
    static constexpr auto PATCH_UI_DIALOGUE_RESULT = u8"patch.ui_dialogue.result";

    static constexpr auto MIGR_UI_DIALOGUE_START = u8"migration.ui_dialogue.start";
    static constexpr auto MIGR_UI_DIALOGUE_FAILED_READ = u8"migration.ui_dialogue.failed.read";
    static constexpr auto MIGR_UI_DIALOGUE_FAILED_WRITE = u8"migration.ui_dialogue.failed.write";
    static constexpr auto MIGR_UI_DIALOGUE_OK_NO_GM_DATA = u8"migration.ui_dialogue.pass.no_gm_data";
    static constexpr auto MIGR_UI_DIALOGUE_OK = u8"migration.ui_dialogue.ok";
    static constexpr auto MIGR_UI_DIALOGUE_RESULT = u8"migration.ui_dialogue.result";
    static constexpr auto MIGR_UI_DIALOGUE_EXTRACT = u8"migration.ui_dialogue.extract";

    static constexpr auto EXTRACT_UI_DIALOGUE_START = u8"patch.ui_dialogue.start";
    static constexpr auto EXTRACT_UI_DIALOGUE_PASS_NO_GM_DATA = u8"extract.ui_dialogue.pass.no_gm_data";
    static constexpr auto EXTRACT_UI_DIALOGUE_FAILED_READ = u8"extract.ui_dialogue.failed.read";
    static constexpr auto EXTRACT_UI_DIALOGUE_FAILED_WRITE = u8"extract.ui_dialogue.failed.write";
    static constexpr auto EXTRACT_UI_DIALOGUE_OK = u8"extract.ui_dialogue.ok";
    static constexpr auto EXTRACT_UI_DIALOGUE_RESULT = u8"extract.ui_dialogue.result";

    // ui-choice
    static constexpr auto PATCH_UI_CHOICE_START = u8"patch.ui_choice.start";
    static constexpr auto PATCH_UI_CHOICE_FAILED_READ = u8"patch.ui_choice.failed.read";
    static constexpr auto PATCH_UI_CHOICE_OK = u8"patch.ui_choice.ok";
    static constexpr auto PATCH_UI_CHOICE_RESULT = u8"patch.ui_choice.result";

    static constexpr auto MIGR_UI_CHOICE_START = u8"migration.ui_choice.start";
    static constexpr auto MIGR_UI_CHOICE_FAILED_READ = u8"migration.ui_choice.failed.read";
    static constexpr auto MIGR_UI_CHOICE_FAILED_WRITE = u8"migration.ui_choice.failed.write";
    static constexpr auto MIGR_UI_CHOICE_OK_NO_GM_DATA = u8"migration.ui_choice.pass.no_gm_data";
    static constexpr auto MIGR_UI_CHOICE_OK = u8"migration.ui_choice.ok";
    static constexpr auto MIGR_UI_CHOICE_RESULT = u8"migration.ui_choice.result";
    static constexpr auto MIGR_UI_CHOICE_EXTRACT = u8"migration.ui_choice.extract";

    static constexpr auto EXTRACT_UI_CHOICE_START = u8"patch.ui_choice.start";
    static constexpr auto EXTRACT_UI_CHOICE_PASS_NO_GM_DATA = u8"extract.ui_choice.pass.no_gm_data";
    static constexpr auto EXTRACT_UI_CHOICE_FAILED_READ = u8"extract.ui_choice.failed.read";
    static constexpr auto EXTRACT_UI_CHOICE_FAILED_WRITE = u8"extract.ui_choice.failed.write";
    static constexpr auto EXTRACT_UI_CHOICE_OK = u8"extract.ui_choice.ok";
    static constexpr auto EXTRACT_UI_CHOICE_RESULT = u8"extract.ui_choice.result";

    // ui-font
    static constexpr auto PATCH_UI_FONT_START = u8"patch.ui_font.start";
    static constexpr auto PATCH_UI_FONT_FAILED_READ = u8"patch.ui_font.failed.read";
    static constexpr auto PATCH_UI_FONT_FAILED_WRITE= u8"patch.ui_font.failed.write";
    static constexpr auto PATCH_UI_FONT_OK = u8"patch.ui_font.ok";
    static constexpr auto PATCH_UI_FONT_RESULT = u8"patch.ui_font.result";

    static constexpr auto MIGR_UI_FONT_START = u8"migration.ui_font.start";
    static constexpr auto MIGR_UI_FONT_FAILED_READ = u8"migration.ui_font.failed.read";
    static constexpr auto MIGR_UI_FONT_FAILED_WRITE= u8"migration.ui_font.failed.write";
    static constexpr auto MIGR_UI_FONT_OK = u8"migration.ui_font.ok";
    static constexpr auto MIGR_UI_FONT_RESULT = u8"migration.ui_font.result";

    static constexpr auto EXTRACT_UI_FONT_START = u8"extract.ui_font.start";
    static constexpr auto EXTRACT_UI_FONT_FAILED_READ = u8"extract.ui_font.failed.read";
    static constexpr auto EXTRACT_UI_FONT_FAILED_WRITE= u8"extract.ui_font.failed.write";
    static constexpr auto EXTRACT_UI_FONT_RESULT = u8"extract.ui_font.result";

    // ui-text
    static constexpr auto PATCH_UI_TEXT_FAILED_READ = u8"extract.ui_text.failed.read";

    // ui-text ingame
    static constexpr auto PATCH_UI_TEXT_IN_GAME_START = u8"patch.ui_text_in_game.start";
    static constexpr auto PATCH_UI_TEXT_IN_GAME_FAILED = u8"patch.ui_text_in_game.failed";
    static constexpr auto PATCH_UI_TEXT_IN_GAME_OK = u8"patch.ui_text_in_game.ok";
    static constexpr auto PATCH_UI_TEXT_IN_GAME_RESULT = u8"patch.ui_text_in_game.result";

    static constexpr auto EXTRACT_UI_TEXT_IN_GAME_START = u8"extract.ui_text_in_game.start";
    static constexpr auto EXTRACT_UI_TEXT_IN_GAME_FAILED = u8"extract.ui_text_in_game.failed";
    static constexpr auto EXTRACT_UI_TEXT_IN_GAME_FAILED_WRITE = u8"extract.ui_text_in_game.failed.write";
    static constexpr auto EXTRACT_UI_TEXT_IN_GAME_OK = u8"extract.ui_text_in_game.ok";
    static constexpr auto EXTRACT_UI_TEXT_IN_GAME_RESULT = u8"extract.ui_text_in_game.result";

    // ui-text setting
    static constexpr auto PATCH_UI_TEXT_SETTING_START = u8"patch.ui_text_setting.start";
    static constexpr auto PATCH_UI_TEXT_SETTING_FAILED = u8"patch.ui_text_setting.failed";
    static constexpr auto PATCH_UI_TEXT_SETTING_OK = u8"patch.ui_text_setting.ok";
    static constexpr auto PATCH_UI_TEXT_SETTING_RESULT = u8"patch.ui_text_setting.result";

    static constexpr auto EXTRACT_UI_TEXT_SETTING_START = u8"extract.ui_text_setting.start";
    static constexpr auto EXTRACT_UI_TEXT_SETTING_FAILED = u8"extract.ui_text_setting.failed";
    static constexpr auto EXTRACT_UI_TEXT_SETTING_FAILED_WRITE = u8"extract.ui_text_setting.failed.write";
    static constexpr auto EXTRACT_UI_TEXT_SETTING_OK = u8"extract.ui_text_setting.ok";
    static constexpr auto EXTRACT_UI_TEXT_SETTING_RESULT = u8"extract.ui_text_setting.result";

    // ui-text dialog
    static constexpr auto PATCH_UI_TEXT_DIALOG_START = u8"patch.ui_text_dialog.start";
    static constexpr auto PATCH_UI_TEXT_DIALOG_FAILED = u8"patch.ui_text_dialog.failed";
    static constexpr auto PATCH_UI_TEXT_DIALOG_OK = u8"patch.ui_text_dialog.ok";
    static constexpr auto PATCH_UI_TEXT_DIALOG_RESULT = u8"patch.ui_text_dialog.result";

    static constexpr auto EXTRACT_UI_TEXT_DIALOG_START = u8"extract.ui_text_dialog.start";
    static constexpr auto EXTRACT_UI_TEXT_DIALOG_FAILED = u8"extract.ui_text_dialog.failed";
    static constexpr auto EXTRACT_UI_TEXT_DIALOG_FAILED_WRITE = u8"extract.ui_text_dialog.failed.write";
    static constexpr auto EXTRACT_UI_TEXT_DIALOG_OK = u8"extract.ui_text_dialog.ok";
    static constexpr auto EXTRACT_UI_TEXT_DIALOG_RESULT = u8"extract.ui_text_dialog.result";

    // ui-text title
    static constexpr auto PATCH_UI_TEXT_TITLE_START = u8"patch.ui_text_title.start";
    static constexpr auto PATCH_UI_TEXT_TITLE_FAILED = u8"patch.ui_text_title.failed";
    static constexpr auto PATCH_UI_TEXT_TITLE_OK = u8"patch.ui_text_title.ok";
    static constexpr auto PATCH_UI_TEXT_TITLE_RESULT = u8"patch.ui_text_title.result";

    static constexpr auto EXTRACT_UI_TEXT_TITLE_START = u8"extract.ui_text_title.start";
    static constexpr auto EXTRACT_UI_TEXT_TITLE_FAILED = u8"extract.ui_text_title.failed";
    static constexpr auto EXTRACT_UI_TEXT_TITLE_FAILED_WRITE = u8"extract.ui_text_title.failed.write";
    static constexpr auto EXTRACT_UI_TEXT_TITLE_OK = u8"extract.ui_text_title.ok";
    static constexpr auto EXTRACT_UI_TEXT_TITLE_RESULT = u8"extract.ui_text_title.result";
};


#endif //RIKKI_PATCHER_WV_WV_INVOKER_HPP
