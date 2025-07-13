#ifndef RIKKI_PATCHER_UTILS_LOGGER_HPP
#define RIKKI_PATCHER_UTILS_LOGGER_HPP
#include "precompiled.hpp"

// log levels
#define VERBOSE Logger::eLogLv::LOG_LV_DEBUG
#define INFO    Logger::eLogLv::LOG_LV_INFO
#define WARN    Logger::eLogLv::LOG_LV_WARN
#define FATAL   Logger::eLogLv::LOG_LV_FATAL

// debug log
#ifdef NDEBUG
    #define DLOG(FMT, ...)
#else
    #define DLOG(FMT, ...) LOG(VERBOSE, FMT, ##__VA_ARGS__)
#endif //NDEBUG

// log
#define LOG(LV, FMT, ...) Logger::log(Logger::Meta{ LV, std::source_location::current(), std::chrono::system_clock::now() }, FMT, ##__VA_ARGS__)

/* logger.hpp
 *  Included classes:
 *      - Logger
 *
 *  Included structs:
 *      - Logger::Meta
 */

// ======================== C L A S S ========================
// ===    Logger
// ======================== C L A S S ========================

class Logger {
public:
    enum class eLogLv : uint8_t {
        LOG_LV_DEBUG = 0,
        LOG_LV_INFO  = 1,
        LOG_LV_WARN  = 2,
        LOG_LV_FATAL = 3
    };

    struct Meta {
        eLogLv m_lv;
        std::source_location m_loc;
        std::chrono::system_clock::time_point m_time;
    };

    template<typename... Args>
    static void log(Meta&& meta, std::string&& fmt, Args&&... args);

private:
    static Logger& instance();
private:
    Logger();
    ~Logger();
private:
    std::ofstream m_ofs;
    kani::OrderedThreadPool m_pool;
};

template<typename ... Args>
void Logger::log(Meta&& meta, std::string&& fmt, Args&&... args) {
    static constexpr std::array<const char*, 4> LV_TO_STR = { "DEBUG", "INFO", "WARN", "FATAL" };
    static                    std::array<ktd::ANSICode, 4> LV_TO_COLOR = { ktd::color::bright_cyan, ktd::color::white, ktd::color::yellow, ktd::color::bright_red };

    Logger::instance().m_pool.enqueue([
        meta = meta,
        fmt = std::move(fmt),
        ... _args = std::forward<Args>(args)
        ]() mutable {

        const auto lv = static_cast<uint8_t>(meta.m_lv);
        const auto time = std::chrono::current_zone()->to_local(meta.m_time);
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count() % 1000;
        const auto fmtTime = std::format("{:%T}.{:03d}", time, ms);

        std::string fmtMsg { };
        
        if constexpr (sizeof...(Args) > 0) {
            fmtMsg = std::vformat(std::string_view(fmt), std::make_format_args(_args...));
        } else {
            fmtMsg = fmt;
        }

        const auto msg = std::format("[{}][{}][{}:{}] {}",
            fmtTime,
            LV_TO_STR[lv],
            path_t(meta.m_loc.file_name()).filename().string(),
            meta.m_loc.line(),
            fmtMsg
        );

        if (auto& ofs = Logger::instance().m_ofs; ofs.good()) {
            ofs << msg << "\n";
            ofs.flush();
        } else {
            std::cerr << "File stream is in error state!" << std::endl;
        }

        std::cout << LV_TO_COLOR[lv] << msg <<  ktd::endl;
    });
}


#endif //RIKKI_PATCHER_UTILS_LOGGER_HPP
