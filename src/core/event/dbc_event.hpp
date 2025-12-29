//
// Created by Adrian Rupp on 29.12.25.
//

#ifndef CANBUSMANAGER_DBC_EVENT_HPP
#define CANBUSMANAGER_DBC_EVENT_HPP
#include "core/dto/DbcDtos.hpp"
#include "event.hpp"

namespace Core {

/**
 * @brief Structure of the event fired when dbc file has successfully been parsed by the CAN Handler.
 */
struct DBCParsedEvent : public Event
{
    Core::DbcConfig config;
    QString filePath;
};

/**
 * @brief Structure of the event fired when dbc file parsing failed.
 */
struct DBCParseErrorEvent : public Event
{
    QString errorMessage;
    QString filePath;
};

/**
 * @brief Structure of the event fired when a dbc file is requested to be parsed.
 */
struct ParseDBCRequestEvent : public Event
{
    QString filePath;
};
}
#endif  // CANBUSMANAGER_DBC_EVENT_HPP
