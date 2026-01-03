#pragma once
#include <string>
#include <typeindex>

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
    std::type_index module_index;

    explicit ModuleStartedEvent(std::type_index index) : module_index(std::move(index)) {}
};

/**
 * @brief Fired when a module stops, containing performance and status data.
 */
struct ModuleStoppedEvent : public Event {
    std::type_index module_index;
    ModuleDiagnostics diagnostics;

    ModuleStoppedEvent(std::type_index index, ModuleDiagnostics diag)
        : module_index(std::move(index)), diagnostics(std::move(diag))
    {
    }
};

}  // namespace Core
