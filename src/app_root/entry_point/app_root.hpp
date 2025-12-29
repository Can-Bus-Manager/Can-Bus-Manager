#pragma once

#include <memory>
#include <vector>

#include "app_root/view/app_root_view.hpp"
#include "core/interface/i_event_broker.hpp"
#include "core/interface/i_lifecycle.hpp"
#include "core/interface/i_tab_component.hpp"

namespace AppRoot {

/**
 * @class AppRoot
 * @brief The central Kernel and Composition Root of the application.
 * * @details
 * This class encapsulates the entire application module. It follows a
 * "Self-Starting" pattern where bootstrap() triggers the internal lifecycle.
 */
class AppRoot
{
   public:
    /**
     * @brief Constructs the AppRoot kernel.
     */
    AppRoot();

    /**
     * @brief Triggers the internal shutdown sequence before destruction.
     * @details Ensures that the private shutdown() is called to release
     * hardware and save state before unique_ptrs clean up memory.
     */
    ~AppRoot();

    /**
     * @brief The sole entry point for the application module.
     * @details
     * 1. Performs Dependency Injection (Model/Delegate into View).
     * 2. Aggregates internal ITabComponents into the m_tabs vector.
     * 3. Calls the private start() method to initiate logic.
     */
    void bootstrap();

    // Deleted copy operations to ensure kernel uniqueness
    AppRoot(const AppRoot&) = delete;
    auto operator=(const AppRoot&) -> AppRoot& = delete;

   private:
    /**
     * @brief Initiates the internal logic and event loops.
     * @details Called automatically at the end of bootstrap().
     */
    void start();

    /**
     * @brief Gracefully stops internal components.
     * @details Called automatically by the destructor.
     */
    void shutdown();

    /**
     * @brief Pointer to the event broker of the application which handles the communication between
     * components.
     * @related Core::IEventBroker
     */
    std::unique_ptr<Core::IEventBroker> m_broker;
    std::unique_ptr<Core::ILifecycle> m_can_handler;

    /**
     * @brief Pointer to the Model component of the app root to instantiate it.
     * @relationship "Instantiates" AppRootModel pointer.
     * @related AppRootModel
     */
    std::unique_ptr<AppRootModel> m_model;

    /**
     * @brief Pointer to the Delegate component of the app root to instantiate it.
     * @relationship "Instantiates" AppRootDelegate pointer.
     * @related AppRootDelegate
     */
    std::unique_ptr<QAbstractItemDelegate> m_delegate;

    /**
     * @brief Pointer to the View component of the app root to instantiate it.
     * @relationship "Instantiates" AppRootView pointer.
     * @related AppRootView
     */
    std::unique_ptr<AppRootView> m_mainView;

    /** * @brief Memory ownership of the tab components.
     * @details The Model only holds raw pointers; this vector ensures the objects
     * live as long as the AppRoot kernel.
     */
    std::vector<std::unique_ptr<Core::ITabComponent>> m_tabs;
};

}  // namespace AppRoot