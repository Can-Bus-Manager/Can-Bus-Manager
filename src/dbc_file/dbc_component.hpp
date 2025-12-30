//
// Created by Adrian Rupp on 29.12.25.
//
#pragma once

#include <memory>

#include "core/event/dbc_event.hpp"

// Core Interfaces
#include "core/interface/i_tab_component.hpp"
#include "core/interface/i_event_broker.hpp"

// MVD Classes
#include "dbc_file/model/dbc_model.hpp"
#include "dbc_file/view/dbc_view.hpp"
#include "delegates.hpp" // Für DbcDelegate

namespace Dbc {
/**
 * @brief The Controller/Manager for the DBC module.
 *
 * RESPONSIBILITIES:
 * - Implements the Core::ITabComponent interface to integrate into the main application.
 * - Owns the Model-View-Delegate stack (Lifecycle Management).
 * - Acts as the bridge between the UI (DbcView) and the System (EventBroker).
 *
 * DATA FLOW:
 * - User Input (View) -> Component -> EventBroker (Publish Command)
 * - System Event (Broker) -> Component -> View (Update UI State)
 * - System Event (Broker) -> Model (Update Data directly)
 */
class DbcComponent : public Core::ITabComponent {
    Q_OBJECT

public:
    /**
     * @brief Constructs the component.
     *
     * Initializes the Model, View, and Delegate, connects signals/slots,
     * and subscribes to relevant system events.
     *
     * @param broker Reference to the system-wide EventBroker.
     */
    explicit DbcComponent(Core::IEventBroker& broker);

    /**
     * @brief Destructor.
     * Cleans up the MVD stack. Connections to the broker are automatically released
     * via the Core::Connection RAII handles.
     */
    ~DbcComponent() override;

    // --- Core::ITabComponent Interface Implementation ---

    /**
     * @brief Returns the main widget (DbcView) for display in the AppRoot.
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
     * @brief Handles the file load request from the View.
     *
     * Triggered when the user drops a file or selects one via dialog.
     * Publishes a ParseDbcRequestEvent to the EventBroker.
     *
     * @param filePath The absolute path to the file.
     */
    void onFileLoadRequested(const QString& filePath);

private:
    /**
     * @brief Callback: Triggered when a DBC file was successfully parsed.
     *
     * Note: The Model updates itself automatically via its own subscription.
     * This callback is used to update the UI state (e.g., unlock navigation sidebar).
     */
    void onDbcParsed(const Core::DBCParsedEvent& event);

    /**
     * @brief Callback: Triggered when parsing failed.
     * Shows an error message to the user (e.g., via QMessageBox).
     */
    void onDbcParseError(const Core::DBCParseErrorEvent& event);

    /**
     * @brief Sets up internal connections between View signals and Component slots.
     */
    void setupConnections();

    // --- Members ---

    // 1. Ownership of MVD Stack
    std::unique_ptr<DbcModel> m_model;       // The Data (Smart Model)
    std::unique_ptr<DbcView> m_view;         // The UI (Composite View)

    // The delegate for generic Hex/Unit formatting (passed to View)
    std::unique_ptr<DbcDelegate> m_delegate;

    // 2. Event Subscriptions (RAII Handles)
    Core::Connection m_parseSuccessConn;
    Core::Connection m_parseErrorConn;
};
}