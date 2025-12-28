#ifndef CANBUSMANAGER_SIGNAL_GRAPH_HPP
#define CANBUSMANAGER_SIGNAL_GRAPH_HPP
#include <QWidget>
#include "monitoring/model/signal_graph_model.hpp"
#include "core/dto/decoded_signal.hpp"

class SignalGraph : QWidget
{
    Q_OBJECT
    public:
        explicit SignalGraph(const DecodedSignal& signal,
                          QWidget* parent = nullptr);
        ~SignalGraph();

        void appendDataToGraph(DecodedSignal& signal);
        void deleteGraph(DecodedSignal& signal);
        void update();

    private:
        SignalGraphModel model;
};

#endif  // CANBUSMANAGER_SIGNAL_GRAPH_HPP
