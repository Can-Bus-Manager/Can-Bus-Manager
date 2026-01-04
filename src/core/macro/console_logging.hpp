#pragma once

#include <chrono>
#include <format>
#include <iomanip>
#include <iostream>
#include <string>

/**
 * @file console_logging.hpp
 * @brief Centralized logging macro controlled by CMAKE_BUILD_TYPE.
 * * LOGGING_LEVEL values:
 * 0: Totally Silent (Production)
 * 1: Errors only
 * 2: Full Debug (Info, Warning, and Error)
 */

#ifndef LOGGING_LEVEL
#define LOGGING_LEVEL 0
#endif

// Color Codes
#define CLR_RST "\033[0m"
#define CLR_ERR "\033[1;31m"
#define CLR_WRN "\033[1;33m"
#define CLR_INF "\033[1;32m"
#define CLR_CLS "\033[1;36m"
#define CLR_DIM "\033[2m"

/**
 * @brief Internal Helper Macro
 * Uses __VA_ARGS__ to support std::format directly inside the macro.
 */
#define PRINT_LOG(color, label, cls, fmt_str, ...)                                               \
    {                                                                                            \
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());       \
        auto tm_struct = std::localtime(&now);                                                   \
        std::string formatted_msg = std::format(fmt_str, ##__VA_ARGS__);                         \
        std::cout << CLR_DIM << std::put_time(tm_struct, "%H:%M:%S") << CLR_RST << color << " [" \
                  << label << "] " << CLR_CLS << "[" << cls << "] " << CLR_RST << formatted_msg  \
                  << std::endl;                                                                  \
    }

// --- Logic for Levels ---

// Level 1 and 2: Show Errors
#if LOGGING_LEVEL >= 1
#define LOG_ERR(cls, fmt_str, ...) PRINT_LOG(CLR_ERR, "ERROR", cls, fmt_str, ##__VA_ARGS__)
#else
#define LOG_ERR(cls, fmt_str, ...)
#endif

// Level 2 only: Show Info and Warnings
#if LOGGING_LEVEL >= 2
#define LOG_INF(cls, fmt_str, ...) PRINT_LOG(CLR_INF, "INFO ", cls, fmt_str, ##__VA_ARGS__)
#define LOG_WRN(cls, fmt_str, ...) PRINT_LOG(CLR_WRN, "WARN ", cls, fmt_str, ##__VA_ARGS__)
#else
#define LOG_INF(cls, fmt_str, ...)
#define LOG_WRN(cls, fmt_str, ...)
#endif