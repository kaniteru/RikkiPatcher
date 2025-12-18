#ifndef RIKKI_PATCHER_PRECOMPILED_HPP
#define RIKKI_PATCHER_PRECOMPILED_HPP

// ============================================================================
// Third-Party Libraries
// ============================================================================
#include <webview.h>
#include <nlohmann/json.hpp>
#include <kani/thread_pool.hpp>
#include <kani/ansi_escapes.hpp>

// ============================================================================
// Windows Headers
// ============================================================================
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>

// ============================================================================
// C++ Standard Library - Core
// ============================================================================
#include <cstdint>
#include <ctime>

// ============================================================================
// C++ Standard Library - Type Support
// ============================================================================
#include <concepts>
#include <type_traits>
#include <typeindex>

// ============================================================================
// C++ Standard Library - Strings
// ============================================================================
#include <string>
#include <string_view>
#include <format>

// ============================================================================
// C++ Standard Library - Containers
// ============================================================================
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <span>
#include <regex>

// ============================================================================
// C++ Standard Library - Algorithms & Ranges
// ============================================================================
#include <algorithm>
#include <ranges>

// ============================================================================
// C++ Standard Library - Memory
// ============================================================================
#include <memory>

// ============================================================================
// C++ Standard Library - Concurrency
// ============================================================================
#include <shared_mutex>

// ============================================================================
// C++ Standard Library - I/O
// ============================================================================
#include <fstream>
#include <iostream>
#include <sstream>

// ============================================================================
// C++ Standard Library - Utilities
// ============================================================================
#include <filesystem>
#include <functional>
#include <optional>
#include <expected>
#include <chrono>
#include <source_location>
#include <utility>

// ============================================================================
// Common Type Aliases
// ============================================================================
namespace fs = std::filesystem;

using path_t = fs::path;
using json_t = nlohmann::json;
using ordered_json_t = nlohmann::ordered_json;


#endif //RIKKI_PATCHER_PRECOMPILED_HPP
