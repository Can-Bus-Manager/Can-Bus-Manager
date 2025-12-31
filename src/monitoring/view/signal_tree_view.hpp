#ifndef CANBUSMANAGER_SIGNAL_TREE_VIEW_HPP
#define CANBUSMANAGER_SIGNAL_TREE_VIEW_HPP
#include <QTreeView>

#include "monitoring/delegate/signal_tree_delegate.hpp"

#endif  // CANBUSMANAGER_SIGNAL_TREE_VIEW_HPP

/**
 * @namespace Monitoring
 * @brief Contains components for CAN signal monitoring and selection.
 */
namespace Monitoring {

/**
 * @class SignalTreeView
 * @brief Tree view widget for displaying available CAN signals.
 *
 * SignalTreeView represents the View layer of the signal selection UI.
 * It displays a hierarchical list of CAN signals provided by a
 * SignalTreeModel and rendered using a SignalTreeDelegate.
 *
 * The class intentionally contains minimal logic and focuses solely on
 * presentation and user interaction, delegating all data management to
 * the model and all rendering customization to the delegate.
 */
class SignalTreeView : public QTreeView
{
    Q_OBJECT
    public:
    /**
     * @brief Constructs the signal tree view widget.
     *
     * @param parent Optional Qt parent widget.
     */
    explicit SignalTreeView(QWidget *parent = nullptr);
};
}  // namespace Monitoring