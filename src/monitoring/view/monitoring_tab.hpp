#ifndef CANBUSMANAGER_MONITORING_TAB_HPP
#define CANBUSMANAGER_MONITORING_TAB_HPP

#include <QSplitter>
#include <QSortFilterProxyModel>

#include "core/dto/can_frame.hpp"
#include "core/interface/IEventBroker.hpp"
#include "core/interface/i_tab_component.hpp"
#include "signal_tree_view.hpp"
#include "graph_list_view.hpp"

#endif  // CANBUSMANAGER_MONITORING_TAB_HPP
namespace Monitoring {
class MonitoringTab : public ITabComponent , public QWidget
{
    Q_OBJECT
    public:
    explicit MonitoringTab(EventBroker* broker, QWidget* parent = nullptr);
    void bootstrap();

private:
    std::unique_ptr<Core::IEventBroker> broker;

    SignalTreeModel* m_treeModel;
    QSortFilterProxyModel* m_treeProxy; //For data filtering

    SignalTreeView* m_signalsView;
    GraphListView* m_graphListView;

    SignalTreeDelegate* m_signalDelegate;

    QSplitter* m_splitter; //For Signals and Graphs scalable split view
};
}