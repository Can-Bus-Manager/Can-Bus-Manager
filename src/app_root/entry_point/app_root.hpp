#pragma once

#include <memory>

#include "app_root/view/app_root_view.hpp"
#include "core/interface/i_event_broker.hpp"

namespace AppRoot {

/**
 * @class AppRoot
 * @brief The central Kernel and Composition Root of the application.
 * * @details 
 * This class serves as the orchestrator for the entire application. 
 * It is responsible for the instantiation of the global event system 
 * and the primary UI compositor.
 * * @note This class has a strong 'Composition' relationship with AppRootView.
 * @see AppRootView
 */
class AppRoot {
public:
    /**
     * @brief Constructs the AppRoot kernel.
     */
    AppRoot();

    /**
     * @brief Ensures orderly destruction of the Broker and View.
     */
    ~AppRoot();

    /**
     * @brief Initializes infrastructure and triggers the UI.
     * * @details
     * 1. Instantiates the concrete EventBroker & CanHandler.
     * 2. Instantiates the AppRootView.
     * 3. Calls AppRootView::render().
     * 4. Publishes the initial AppStartedEvent.
     */
    void bootstrap();

    // Deleted copy operations to ensure kernel uniqueness
    AppRoot(const AppRoot&) = delete;
    auto operator=(const AppRoot&) -> AppRoot& = delete;

private:
    /** * @brief The communication backbone.
     * @relationship "Owns"
     */
    std::unique_ptr<Core::IEventBroker> m_broker;

    /** * @brief The root UI compositor.
     * @relationship "Requires/Owns"
     */
    std::unique_ptr<AppRootView> m_view;
};

} // namespace AppRoot