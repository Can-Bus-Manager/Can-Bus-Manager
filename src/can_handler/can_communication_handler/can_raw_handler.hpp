//
// Created by flori on 28.12.2025.
//

#ifndef CANBUSMANAGER_CAN_RAW_HANDLER_HPP
#define CANBUSMANAGER_CAN_RAW_HANDLER_HPP
#include "core/event/can_event.hpp"
#include "i_can_parser.hpp"

namespace CanHandler {
class CanRawHandler final : ICanParser
{
   public:
    explicit CanRawHandler(Core::IEventBroker& eventBroker) : ICanParser(eventBroker)
    {
        rawSendEventConnection = eventBroker.subscribe<Core::SendCanMessageRawEvent>(
            [this](const Core::SendCanMessageRawEvent& event) -> void {
                handleSendMessage(event);
            });
    };
    ~CanRawHandler() override = default;
    void parseReceivedMessage(const sockcanpp::CanMessage* canMessage) override;
    void handleSendMessage(const Core::SendCanMessageRawEvent& event);

   private:
    Core::Connection rawSendEventConnection;
};
}  // namespace CanHandler

#endif  // CANBUSMANAGER_CAN_RAW_HANDLER_HPP
