//
// Created by flori on 05.01.2026.
//

#ifndef CANBUSMANAGER_DBC_PARSER_HPP
#define CANBUSMANAGER_DBC_PARSER_HPP
#include <string>

#include "core/dto/dbc_dto.hpp"
namespace CanHandler {
class DbcParser
{
public:
    /**
     * @brief Tries to parse the provided string to a DBC object
     * @param file The dbc file parsed to a single string
     */
    auto parseDbc(std::string& file) -> Core::DbcConfig;
private:
    /**
     * @brief tries to parse the start of the provided file to a signal (SG_:)
     * @param file The provided rest of a DBC file (truncated to after the signal if a signal is
     * parsed)
     * @return The parsed signal or a null pointer if no signal was parsed
     */
    auto parseSignal(std::string& file) -> Core::DbcSignalDescription;
    /**
     * @brief tries to parse the start of the provided file to a message (BO_:)
     * @param file The provided rest of a DBC file (truncated to after the signal if a message is
     * parsed)
     * @return The parsed message or a null pointer if no message was parsed
     */
    auto parseMessage(std::string& file) -> Core::DbcMessageDescription;
    /**
     * @brief tries to parse the start of the provided file to a value description
     * @param file The provided rest of a DBC file (truncated to after the value description if a
     * message is parsed)
     * @return The parsed value description or a null pointer if no value description was parsed
     */
    auto parseValueDescription(std::string& file) -> Core::DbcValueDescription;
    /**
     * @brief tries to parse the start of the provided file to a signal value description (VAL_:)
     * @param file The provided rest of a DBC file (truncated to after the signal value description
     * if a message is parsed)
     * @return The parsed signal value description or a null pointer if no signal value description
     * was parsed
     */
    auto parseSignalValue(std::string& file) -> Core::DbcSignalValueDescription;
    /**
     * @brief tries to parse the start of the provided file to a list of nodes (BU_:)
     * @param file The provided rest of a DBC file
     * (truncated to after the signal if a list of nodes is parsed)
     * @return The parsed list of nodes or a null pointer if no list of nodes was parsed
     */
    auto parseNodes(std::string& file) -> std::list<std::string>;
    /**
     * @brief tries to parse the start of the provided file to a comment (CM_:)
     * @param file The provided rest of a DBC file
     * (truncated to after the signal if a comment is parsed)
     * @return The parsed comment or a null pointer if no comment was parsed
     */
    auto parseComment(std::string& file) -> std::string;
};
}
#endif  // CANBUSMANAGER_DBC_PARSER_HPP
