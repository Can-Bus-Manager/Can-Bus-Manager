//
// Created by Lino on 17.12.2025.
//

#ifndef CANBUSSIMULATOR_EVENTBROKER_HPP
#define CANBUSSIMULATOR_EVENTBROKER_HPP

#include <entt/entt.hpp>
#include "core/interface/IEventBroker.hpp"

/** TEST */
class EventBroker final : IEventBroker {
    public:
    void update() override;

   protected:
    void publishImpl(std::type_index type, const void* event) override;
    void enqueueImpl(std::type_index type, const void* event) override;

    void subscribeImpl(
        std::type_index type,
        std::function<void(const void*)> callback
    ) override;

    void unsubscribeAllImpl(std::type_index type) override;

   private:
    entt::dispatcher dispatcher;
};

#endif  // CANBUSSIMULATOR_EVENTBROKER_HPP