//
// Created by flori on 30.12.2025.
//

#ifndef CANBUSMANAGER_DBC_HANDLER_HPP
#define CANBUSMANAGER_DBC_HANDLER_HPP
#include "core/event/dbc_event.hpp"
#include "core/interface/i_lifecycle.hpp"
namespace CanHandler {
class DbcHandler final: Core::ILifecycle
{
public:
    explicit DbcHandler(Core::IEventBroker& eventBroker) : Core::ILifecycle(eventBroker)
    {
        parseNewDbcConnection = eventBroker.subscribe<Core::ParseDBCRequestEvent>(
            [this](const Core::ParseDBCRequestEvent& event) -> void { parseNewDbc(event); });
    };
    ~DbcHandler() override;
protected:
    void onStart() override;
    void onStop() override;
private:
    /**
     * @brief Function called on the @ref [Core::ParseDBCRequestEvent] event, tries to parse the provided
     * DBC, publishes an Event on success/fail
     * @param event The @ref [Core::ParseDBCRequestEvent] to parse a new DBC
     */
    void parseNewDbc(const Core::ParseDBCRequestEvent& event);
    /**
     * @brief tries to parse the start of the provided file to a signal (SG_:)
     * @param file The provided rest of a DBC file (truncated to after the signal if a signal is parsed)
     * @return The parsed signal or a null pointer if no signal was parsed
     */
    auto parseSignal(std::string& file) -> Core::DbcSignalDescription;
    /**
     * @brief tries to parse the start of the provided file to a message (BO_:)
     * @param file The provided rest of a DBC file (truncated to after the signal if a message is parsed)
     * @return The parsed message or a null pointer if no message was parsed
     */
    auto parseMessage(std::string& file) -> Core::DbcMessageDescription;
    /**
     * @brief tries to parse the start of the provided file to a value description
     * @param file The provided rest of a DBC file (truncated to after the value description if a message is parsed)
     * @return The parsed value description or a null pointer if no value description was parsed
     */
    auto parseValue(std::string& file) -> Core::DbcValueDescription;
    /**
     * @brief tries to parse the start of the provided file to a signal value description (VAL_:)
     * @param file The provided rest of a DBC file (truncated to after the signal value description if a message is parsed)
     * @return The parsed signal value description or a null pointer if no signal value description was parsed
     */
    auto parseSignalValue(std::string& file) -> Core::DbcSignalValueDescription;
    /**
     * @brief tries to parse the start of the provided file to a list of nodes (BU_:)
     * @param file The provided rest of a DBC file (truncated to after the signal if a list of nodes is parsed)
     * @return The parsed list of nodes or a null pointer if no list of nodes was parsed
     */
    auto parseNodes(std::string& file) -> std::list<std::string>;
    /**
     * @brief tries to parse the start of the provided file to a comment (CM_:)
     * @param file The provided rest of a DBC file (truncated to after the signal if a comment is parsed)
     * @return The parsed comment or a null pointer if no comment was parsed
     */
    auto parseComment(std::string& file) -> std::string;

    Core::Connection parseNewDbcConnection;
};
}
#endif //CANBUSMANAGER_DBC_HANDLER_HPP
