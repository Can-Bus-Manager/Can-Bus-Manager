//
// Created by flori on 28.12.2025.
//

#ifndef CANBUSMANAGER_CAN_COMMUNICATION_HANDLER_HPP
#define CANBUSMANAGER_CAN_COMMUNICATION_HANDLER_HPP
#include <list>

#include "core/interface/i_lifecycle.hpp"
#include "i_can_parser.hpp"

namespace CanHandler {
class CanCommunicationHandler final : Core::ILifecycle
{
   public:
    explicit CanCommunicationHandler(Core::IEventBroker& event_broker)
        : ILifecycle(event_broker) {

          };
    /**
     * @brief Called automatically when the application publishes AppStartedEvent.
     */
    void onStart() override;
    /**
     * @brief Called automatically when the application publishes AppStoppedEvent.
     */
    void onStop() override;

   private:
    std::list<ICanParser> can_handlers;
};
}  // namespace CanHandler

#endif  // CANBUSMANAGER_CAN_COMMUNICATION_HANDLER_HPP
