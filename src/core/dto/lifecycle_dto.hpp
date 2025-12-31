#pragma once
#include <chrono>
#include <string>

namespace Core {
/**
 * @brief Diagnostics data for a module shutdown.
 * If the module had to shut down due to an error, it will be visible in this dto.
 */
struct ModuleDiagnostics {
    std::chrono::milliseconds runtime;
    bool wasError;
    std::string errorMessage;
};
}  // namespace Core
