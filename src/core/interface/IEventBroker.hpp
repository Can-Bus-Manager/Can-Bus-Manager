//
// Created by flori on 27.12.2025.
//

#ifndef CANBUSMANAGER_IEVENTBROKER_H
#define CANBUSMANAGER_IEVENTBROKER_H

#include <typeindex>
#include <functional>

class IEventBroker {
public:
    virtual ~IEventBroker() = default;

    // Publishing

    /// Immediately dispatch an event to all subscribers
    template<typename Event>
    void publish(const Event& event) {
        publishImpl(std::type_index(typeid(Event)), &event);
    }

    /// Queue an event for later dispatch
    template<typename Event>
    void enqueue(const Event& event) {
        enqueueImpl(std::type_index(typeid(Event)), &event);
    }

    /// Process queued events
    virtual void update();

    // Subscription

    /// Subscribe a callback to an event type
    template<typename Event>
    void subscribe(std::function<void(const Event&)> callback) {
        subscribeImpl(
            std::type_index(typeid(Event)),
            [cb = std::move(callback)](const void* evt) {
                cb(*static_cast<const Event*>(evt));
            }
        );
    }

    /// Unsubscribe all callbacks for an event type
    template<typename Event>
    void unsubscribeAll() {
        unsubscribeAllImpl(std::type_index(typeid(Event)));
    }

protected:
    //  Type-erased virtual interface
    virtual void publishImpl(std::type_index type, const void* event);
    virtual void enqueueImpl(std::type_index type, const void* event);

    virtual void subscribeImpl(
        std::type_index type,
        std::function<void(const void*)> callback
    );

    virtual void unsubscribeAllImpl(std::type_index type);
};

#endif  // CANBUSMANAGER_IEVENTBROKER_H
