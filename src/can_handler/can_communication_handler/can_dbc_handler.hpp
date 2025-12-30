//
// Created by flori on 28.12.2025.
//

#ifndef CANBUSMANAGER_CAN_DBC_HANDLER_HPP
#define CANBUSMANAGER_CAN_DBC_HANDLER_HPP
#include "core/event/can_event.hpp"
#include "core/event/dbc_event.hpp"
#include "i_can_parser.hpp"

namespace CanHandler {
class CanDbcHandler final : public ICanParser
{
   public:
    explicit CanDbcHandler(Core::IEventBroker& eventBroker) : ICanParser(eventBroker)
    {
        dbcSendEventConnection = eventBroker.subscribe<Core::SendCanMessageDbc>(
            [this](const Core::SendCanMessageDbc& event) -> void { handleSendMessage(event); });
        dbcConfigChangeConnection = eventBroker.subscribe<Core::DBCParsedEvent>(
            [this](const Core::DBCParsedEvent& event) -> void { handleNewDbc(event); });
    };
    ~CanDbcHandler() override = default;
private:
    void parseReceivedMessage(const sockcanpp::CanMessage* canMessage) override;
    void handleSendMessage(const Core::SendCanMessageDbc& event);
    void handleNewDbc(const Core::DBCParsedEvent& event);

    Core::Connection dbcSendEventConnection;
    Core::Connection dbcConfigChangeConnection;
};
}  // namespace CanHandler

#endif  // CANBUSMANAGER_CAN_DBC_HANDLER_HPP
