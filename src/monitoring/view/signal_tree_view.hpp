#ifndef CANBUSMANAGER_SIGNAL_TREE_VIEW_HPP
#define CANBUSMANAGER_SIGNAL_TREE_VIEW_HPP
#include <QTreeView>

#include "monitoring/delegate/signal_tree_delegate.hpp"
#include "monitoring/model/signal_tree_model.hpp"

#endif  // CANBUSMANAGER_SIGNAL_TREE_VIEW_HPP
namespace Monitoring {
class SignalTreeView : public QTreeView
{
    Q_OBJECT
    public:
    explicit SignalTreeView(QWidget *parent = nullptr);
};
}