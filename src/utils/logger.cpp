#include "logger.hpp"
#include "rikki/dir_mgr.hpp"
#include "rikki/dir_mgr_enum.hpp"

namespace {

constexpr std::array<const char*, 5> LEVEL_NAMES = { "V", "DEBUG", "INFO", "WARN", "FATAL" };
constexpr std::array<const char*, 5> LEVEL_COLORS = {
    kani::ansi::fg_bright_white,
    kani::ansi::fg_bright_cyan,
    kani::ansi::fg_white,
    kani::ansi::fg_yellow,
    kani::ansi::fg_bright_red
};
} //namespace

// ======================== C L A S S ========================
// ===    Logger
// ======================== C L A S S ========================

void Logger::log_impl(eLogLv level, const std::source_location& loc, std::string&& message) {
    m_pool.enqueue([this, level, loc, msg = std::move(message)]() {
        const auto lvIndex = static_cast<size_t>(level);
        const auto now = std::chrono::system_clock::now();

        // Format timestamp
        const auto localTime = std::chrono::current_zone()->to_local(now);
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            localTime.time_since_epoch()).count() % 1000;

        // Build log line
        const auto filename = path_t(loc.file_name()).filename().string();
        const auto logLine = std::format("[{:%T}.{:03d}][{}][{}:{}] {}",
            localTime, ms,
            LEVEL_NAMES[lvIndex],
            filename,
            loc.line(),
            msg);

        // Write to file
        if (m_ofs.good()) {
            m_ofs << logLine << '\n';
            m_ofs.flush();
        }

        // Write to console with color
        std::cout << LEVEL_COLORS[lvIndex] << logLine << kani::ansi::reset_fg << std::endl;
    });
}

Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

Logger::Logger() :
    m_ofs(DirMgr::get(eDir::DIR_PROJ_LOG), std::ios::out | std::ios::trunc) {

    kani::ansi::enable_virtual_terminal();
    m_pool.start();
}

Logger::~Logger() {
    while (!m_pool.is_empty()) {
        std::this_thread::yield();
    }
    m_pool.stop();

    if (m_ofs.is_open()) {
        m_ofs.close();
    }
}
