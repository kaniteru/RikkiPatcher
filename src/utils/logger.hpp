#ifndef RIKKI_PATCHER_UTILS_LOGGER_HPP
#define RIKKI_PATCHER_UTILS_LOGGER_HPP
#include "precompiled.hpp"

/* logger.hpp
 *  Included classes:
 *      - Logger
 */

// ======================== C L A S S ========================
// ===    Logger
// ======================== C L A S S ========================

class Logger {
public:
    /**
     * @brief Log severity levels.
     */
    enum class eLogLv : uint8_t {
        LOG_LV_DEBUG = 0,
        LOG_LV_VERBOSE,
        LOG_LV_INFO,
        LOG_LV_WARN,
        LOG_LV_FATAL
    };

    /**
     * @brief Log a formatted message.
     *
     * @tparam Args Format argument types.
     * @param level Log level.
     * @param loc Source location.
     * @param fmt Format string.
     * @param args Format arguments.
     */
    template<typename... Args>
    static void log(eLogLv level, const std::source_location& loc,
                    std::format_string<Args...> fmt, Args&&... args);
private:
    void log_impl(eLogLv level, const std::source_location& loc, std::string&& message);

    static Logger& instance();
private:
    Logger();
    ~Logger();
private:
    std::ofstream m_ofs;
    kani::OrderedThreadPool m_pool;
};

template<typename ... Args>
void Logger::log(const eLogLv level, const std::source_location& loc, std::format_string<Args...> fmt,
    Args&&... args) {
    instance().log_impl(level, loc, std::format(fmt, std::forward<Args>(args)...));
}

// ============================================================================
// Log Macros
// ============================================================================
#define LOG_VERBOSE(FMT, ...) \
    Logger::log(Logger::eLogLv::LOG_LV_VERBOSE, std::source_location::current(), FMT, ##__VA_ARGS__)
#define LOG_INFO(FMT, ...) \
    Logger::log(Logger::eLogLv::LOG_LV_INFO, std::source_location::current(), FMT, ##__VA_ARGS__)
#define LOG_WARN(FMT, ...) \
    Logger::log(Logger::eLogLv::LOG_LV_WARN, std::source_location::current(), FMT, ##__VA_ARGS__)
#define LOG_FATAL(FMT, ...) \
    Logger::log(Logger::eLogLv::LOG_LV_FATAL, std::source_location::current(), FMT, ##__VA_ARGS__)

#ifdef NDEBUG
    #define LOG_DEBUG(FMT, ...) \
        ((void)0)
#else
    #define LOG_DEBUG(FMT, ...) \
        Logger::log(Logger::eLogLv::LOG_LV_DEBUG, std::source_location::current(), FMT, ##__VA_ARGS__)
#endif //NDEBUG


#endif //RIKKI_PATCHER_UTILS_LOGGER_HPP
