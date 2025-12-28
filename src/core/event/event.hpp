#pragma once

namespace Core {

/**
 * @brief Marker interface for all valid events in the system.
 */
struct Event {
    virtual ~Event() = default;
};

}  // namespace Core
