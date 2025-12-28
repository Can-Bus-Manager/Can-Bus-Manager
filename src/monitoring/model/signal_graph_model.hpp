#ifndef CANBUSMANAGER_SIGNAL_GRAPH_MODEL_HPP
#define CANBUSMANAGER_SIGNAL_GRAPH_MODEL_HPP

#include <QObject>
#include "core/dto/decoded_signal.hpp"

#endif  // CANBUSMANAGER_SIGNAL_GRAPH_MODEL_HPP

class SignalGraphModel : public QObject {
    Q_OBJECT

    public:
        explicit SignalGraphModel(QObject* parent = nullptr);

    public slots:
        void addSignal(const DecodedSignal& signal);
        void removeSignal(const DecodedSignal& signal);
};