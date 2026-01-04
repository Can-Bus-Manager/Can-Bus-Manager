#ifndef CANBUSMANAGER_MONITORING_TAB_HPP
#define CANBUSMANAGER_MONITORING_TAB_HPP

#include <QSortFilterProxyModel>
#include <QSplitter>

#include "core/interface/i_event_broker.hpp"
#include "core/interface/i_tab_component.hpp"
#include "graph_list_view.hpp"
#include "monitoring/model/signal_tree_model.hpp"
#include "signal_tree_view.hpp"

#endif  // CANBUSMANAGER_MONITORING_TAB_HPP

/**
 * @namespace Monitoring
 * @brief Contains UI components related to CAN signal monitoring and
 * visualization.
 */
namespace Monitoring {

/**
 * @class MonitoringComponent
 * @brief UI tab component responsible for monitoring CAN signals and
 * managing their visualization.
 *
 * MonitoringComponent integrates a hierarchical signal tree with a graph list
 * view to allow users to inspect available CAN signals and select signals
 * for graphical visualization. The component subscribes to system events
 * via the event broker and acts as a composition root for its internal
 * models, views, and delegates.
 *
 * Architectural roles:
 * - UI tab entry (via ITabComponent)
 * - Event consumer / dispatcher (via IEventBroker)
 * - MVC coordinator for signal models and views
 */
class MonitoringComponent : public Core::ITabComponent, public QWidget
{
    Q_OBJECT
   public:
    /**
     * @brief Constructs the Monitoring tab.
     *
     * @param broker Pointer to the global event broker used for subscribing
     *               to and emitting application-wide events.
     */
    explicit MonitoringComponent(Core::IEventBroker& broker);

    /**
     * @brief Returns the main widget (MonitoringView) for display in the application window.
     * @caller AppRoot.
     */
    auto getView() -> QWidget* override;

    /**
     * @brief Called when the application starts/module is activated.
     */
    void onStart() override;

    /**
     * @brief Called when the application stops/module is deactivated.
     */
    void onStop() override;

   private:
    /**
     * @brief Event broker used for decoupled communication with other
     * components.
     *
     * Ownership is transferred to this component to ensure a well-defined
     * lifecycle and prevent dangling subscriptions.
     */
    std::unique_ptr<Core::IEventBroker> broker;

    /**
     * @brief Model representing the hierarchical structure of CAN signals.
     *
     * Typically populated from a parsed DBC file and updated as new signals
     * become available.
     */
    SignalTreeModel* m_treeModel;

    /**
     * @brief Proxy model used to filter and sort the signal tree data.
     *
     * Enables search, category filtering, and dynamic visibility of signals
     * without modifying the underlying model.
     */
    QSortFilterProxyModel* m_treeProxy;  // For data filtering

    /**
     * @brief View displaying the hierarchical signal tree.
     *
     * Acts as the primary interaction point for selecting signals.
     */
    SignalTreeView* m_signalsView;

    /**
     * @brief View displaying graphs associated with selected CAN signals.
     *
     * Each entry represents a signal plotted over time.
     */
    GraphListView* m_graphListView;

    /**
     * @brief Delegate responsible for custom rendering and interaction logic
     *        of signal tree items.
     *
     * Handles formatting, icons, and user interaction behavior at the item
     * level.
     */
    SignalTreeDelegate* m_signalDelegate;

    /**
     * @brief Splitter enabling resizable layout between signal selection
     *        and graph visualization areas.
     */
    QSplitter* m_splitter;  // For Signals and Graphs scalable split view
};
}  // namespace Monitoring