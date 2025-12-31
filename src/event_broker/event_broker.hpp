//
// Created by Lino on 17.12.2025.
//

#ifndef CANBUSSIMULATOR_EVENTBROKER_HPP
#define CANBUSSIMULATOR_EVENTBROKER_HPP

#include <entt/entt.hpp>

#include "core/interface/i_event_broker.hpp"
namespace EventBroker {
class EventBroker final : Core::IEventBroker
{
   protected:
    void _publish(std::type_index type, const void* data) override;
    auto _subscribe(std::type_index type, std::function<void(const void*)> callback)
        -> Core::Connection override;

   private:
    struct Channel {
        entt::dispatcher dispatcher;

        void trigger(const void* event)
        {
            dispatcher.trigger(event);
        }

        auto sink()
        {
            return dispatcher.sink<const void*>();
        }
    };

    auto getChannel(const std::type_index type) -> Channel&
    {
        auto& ptr = channels[type];
        if (!ptr)
        {
            ptr = std::make_unique<Channel>();
        }
        return *ptr;
    }

    std::unordered_map<std::type_index, std::unique_ptr<Channel>> channels;
};
}  // namespace EventBroker

#endif  // CANBUSSIMULATOR_EVENTBROKER_HPP