//
// Created by flori on 28.12.2025.
//

#ifndef CANBUSMANAGER_I_CAN_HANDLER_HPP
#define CANBUSMANAGER_I_CAN_HANDLER_HPP
#include "CanMessage.hpp"
#include "core/interface/i_event_broker.hpp"


namespace CanHandler {
class ICanParser {
public:
    explicit ICanParser(Core::IEventBroker& eventBroker) : broker(eventBroker) {}
    virtual ~ICanParser() = default;
    virtual void parseReceivedMessage(const sockcanpp::CanMessage* canMessage);
private:
    Core::IEventBroker& broker;
};
}

#endif //CANBUSMANAGER_I_CAN_HANDLER_HPP
