//
#pragma once

#include <memory>

// Core Interfaces
#include "core/interface/i_event_broker.hpp"
#include "core/interface/i_tab_component.hpp"

// MVD Classes
#include "logging/delegate/logging_delegate.hpp"
#include "logging/model/logging_model.hpp"
#include "logging/view/logging_view.hpp"

// Forward declarations for Events
namespace Core {
struct SignalLoggedEvent;
struct LoggingErrorEvent;
}  // namespace Core

namespace Logging {

/**
 * @class LoggingComponent
 * @brief The Controller/Composition Root for the Logging module.
 *
 * @details
 * **RESPONSIBILITIES:**
 * - Implements the `Core::ITabComponent` interface to integrate into the AppRoot.
 * - **Lifecycle Management:** Creates and owns the Model, View, and Delegate.
 * - **Wiring:** Connects the View (Signals) to the System (EventBroker) and vice versa.
 *
 * **DATA FLOW:**
 * - User Input (View) -> Component -> EventBroker (Publish `ParseDbcRequestEvent`)
 * - System Event (`SignalLoggedEvent`) -> Model (Update Data)
 */
class LoggingComponent : public Core::ITabComponent
{
    Q_OBJECT

   public:
    /**
     * @brief Constructs the component.
     *
     * @caller AppRoot (Module Loader).
     *
     * @details
     * Initializes the MVD stack, connects signals/slots, and subscribes to system events.
     *
     * @param broker Reference to the system-wide EventBroker.
     */
    explicit LoggingComponent(Core::IEventBroker& broker);

    /**
     * @brief Destructor.
     * Cleans up the MVD stack. Broker connections are released automatically via RAII.
     */
    ~LoggingComponent() override;

    // --- Core::ITabComponent Interface Implementation ---

    /**
     * @brief Returns the main widget (LoggingView) for display in the application window.
     * @caller AppRoot.
     */
    auto getView() -> QWidget* override;

    // --- Core::ILifecycle Interface Implementation ---

    /**
     * @brief Called when the application starts/module is activated.
     */
    void onStart() override;

    /**
     * @brief Called when the application stops/module is deactivated.
     */
    void onStop() override;

   private slots:
    /**
     * @brief Slot: Triggered when the user clicks the "Export" button in the View.
     *
     * @caller LoggingView (signal).
     *
     * @details
     * Gathers current log data from the Model and initiates export logic
     * (e.g., saving to CSV file). Actual file dialog and writing logic
     * would be implemented here or delegated to a helper class.
     */
    void onExportRequested();

   private:
    /**
     * @brief Callback: Triggered when a new signal log event is published.
     * @caller EventBroker (lambda callback).
     * @details Appends the new log entry to the Model.
     */
    void onSignalLogged(const Core::SignalLoggedEvent& event);

    /**
     * @brief Callback: Triggered when a logging error event is published.
     * @caller EventBroker (lambda callback).
     * @details Displays an error message to the user via the View.
     */
    void onLoggingError(const Core::LoggingErrorEvent& event);

    /**
     * @brief Sets up internal connections between View signals and Component slots.
     * @caller Constructor.
     */
    void setupConnections();

    // --- Members ---

    /** @brief Ownership of the Data Model (Smart Model). */
    std::unique_ptr<LoggingModel> m_model;

    /** @brief Ownership of the Composite View. */
    std::unique_ptr<LoggingView> m_view;

    /** @brief Ownership of the Formatting Delegate (passed to View). */
    std::unique_ptr<LoggingDelegate> m_delegate;
    /** @brief RAII Handle for signal log event subscription. */
    Core::Connection m_signalLoggedConn;

    /** @brief RAII Handle for logging error event subscription. */
    Core::Connection m_loggingErrorConn;
};

}  // namespace Logging