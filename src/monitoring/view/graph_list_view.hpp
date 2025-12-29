#ifndef CANBUSMANAGER_GRAPH_LIST_VIEW_HPP
#define CANBUSMANAGER_GRAPH_LIST_VIEW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include "signal_graph.hpp"

#endif  // CANBUSMANAGER_GRAPH_LIST_VIEW_HPP

namespace Monitoring {
class GraphListView : public QWidget {
    Q_OBJECT
public:
    explicit GraphListView(QWidget* parent = nullptr);

    void appendDataToGraph(DecodedSignal& signal);

    void deleteGraph(DecodedSignal& signal);

private:
    QVBoxLayout* m_layout;
    QScrollArea* m_scrollArea;
    QList<SignalGraph*> m_signal_graphs;

    void newGraph(DecodedSignal& signal);
};
}