#pragma once
#include <string>

#include "core/dto/lifecycle_dto.hpp"
#include "event.hpp"

namespace Core {

/**
 * @brief Structure of the app start event fired when the application starts.
 */
struct AppStartedEvent : public Event {
};

/**
 * @brief Structure of the app stop event fired when the application stops.
 */
struct AppStoppedEvent : public Event {
};

/**
 * @brief Fired when a module of the application starts.
 */
struct ModuleStartedEvent : public Event {
    std::string moduleName;

    explicit ModuleStartedEvent(std::string name) : moduleName(std::move(name)) {}
};

/**
 * @brief Fired when a module stops, containing performance and status data.
 */
struct ModuleStoppedEvent : public Event {
    std::string moduleName;
    ModuleDiagnostics diagnostics;

    ModuleStoppedEvent(std::string name, ModuleDiagnostics diag)
        : moduleName(std::move(name)), diagnostics(std::move(diag))
    {
    }
};

}  // namespace Core
