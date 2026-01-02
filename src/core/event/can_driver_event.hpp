//
// Created by flori on 02.01.2026.
//

#ifndef CANBUSMANAGER_CAN_DRIVER_EVENT_HPP
#define CANBUSMANAGER_CAN_DRIVER_EVENT_HPP
#include <string>

#include "event.hpp"
namespace Core {
class CanDriverChangeEvent final : Event
{
    std::string deviceName;
};
}  // namespace Core
#endif  // CANBUSMANAGER_CAN_DRIVER_EVENT_HPP
