//
// Created by flori on 28.12.2025.
//

#ifndef CANBUSMANAGER_CAN_EVENT_HPP
#define CANBUSMANAGER_CAN_EVENT_HPP
#include <array>
#include <ctime>
#include <string>
#include <unordered_map>

#include "event.hpp"
namespace Core {
/**
 * @brief Structure of the received can event when a can message is received and used in raw form
 */
struct ReceivedCanRaw final : public Event
{
    std::time_t receiveTime;
    std::array<char, 8> data;
    char messageId;
};
/**
 * @brief Structure of the received can event when a can message is received and used in dbc decoded
 * form
 */
struct ReceivedCanDbc final : public Event
{
    std::time_t receiveTime;
    std::unordered_map<std::string, double> parsedMessage;
    char messageId;
};
/**
 * @brief Structure of the send can event, when an already encoded message should be sent
 */
struct SendCanMessageRaw final : public Event
{
    std::array<char, 8> data;
    char messageId;
};
/**
 * @brief Structure of the send can event, when a message should be sent based on the current DBC
 * config
 */
struct SendCanMessageDbc final : public Event
{
    std::unordered_map<std::string, double> values;
    char messageId;
};
};  // namespace Core
#endif  // CANBUSMANAGER_CAN_EVENT_HPP
