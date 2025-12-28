#ifndef CANBUSMANAGER_SIGNAL_TREE_MODEL_HPP
#define CANBUSMANAGER_SIGNAL_TREE_MODEL_HPP
#include <QAbstractItemModel>
#include "core/dto/can_frame.hpp"
#include "core/dto/decoded_signal.hpp"

#endif  // CANBUSMANAGER_SIGNAL_TREE_MODEL_HPP

class SignalTreeModel : public QAbstractItemModel {
    Q_OBJECT
    public:
        explicit SignalTreeModel(QObject* parent = nullptr);

        QModelIndex index(int row, int column,
                      const QModelIndex& parent) const override;
        QModelIndex parent(const QModelIndex& index) const override;
        int rowCount(const QModelIndex& parent) const override;
        int columnCount(const QModelIndex& parent) const override;
        QVariant data(const QModelIndex& index, int role) const override;
        Qt::ItemFlags flags(const QModelIndex& index) const override;
        bool setData(const QModelIndex& index,
                 const QVariant& value,
                 int role) override;

    public slots:
        void onFrameReceived(const CanFrame& frame);

    signals:
        void signalChecked(const DecodedSignal& signal);
        void signalUnchecked(const DecodedSignal& signal);

    private:
        struct SignalNode {
            DecodedSignal signal;
            Qt::CheckState checked;
        };

        struct FrameNode {
            CanFrame frame;
            QVector<SignalNode> signals;
            Qt::CheckState checked;
        };

    QVector<FrameNode> m_frames;  // contains last 1min/whatever of signal data
};