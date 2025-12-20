//
// Created by Lino on 17.12.2025.
//

#ifndef CANBUSSIMULATOR_EVENTBROKER_HPP
#define CANBUSSIMULATOR_EVENTBROKER_HPP

#include <entt/entt.hpp>

/** TEST */
class EventBroker {
public:
    template<typename T>
    void trigger(const T& event) {
        dispatcher.trigger(event);
    }

    template<typename T>
    void enqueue(const T& event) {
        dispatcher.enqueue(event);
    }

    void update();

    entt::dispatcher& getDispatcher() { return dispatcher; }

private:
    entt::dispatcher dispatcher;
};

#endif //CANBUSSIMULATOR_EVENTBROKER_HPP