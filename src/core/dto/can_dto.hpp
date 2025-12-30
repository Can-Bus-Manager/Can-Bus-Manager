//
// Created by flori on 29.12.2025.
//

#ifndef CANBUSMANAGER_CAN_DTO_HPP
#define CANBUSMANAGER_CAN_DTO_HPP
#include <array>
#include <ctime>
#include <list>
#include <string>

namespace Core {
struct RawCanMessage {
    std::time_t receiveTime;
    std::array<char, 8> data;
    char messageId;
};
struct DbcCanMessage {
    std::time_t receiveTime;
    std::list<DbcCanMessage> signalValues;
    char messageId;
};
struct DbcCanSignal {
    std::string name;
    double value;
};
}  // namespace Core
#endif  // CANBUSMANAGER_CAN_DTO_HPP
