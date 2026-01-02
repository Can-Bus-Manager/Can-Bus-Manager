#ifndef SENDINGMODEL_H
#define SENDINGMODEL_H
#include <QAbstractTableModel>
#include <QTimer>
#include <cstdint>
#include <vector>

#include "core/interface/i_event_broker.hpp"

namespace Sending {
class SendingModel : public QAbstractTableModel
{
    Q_OBJECT

   public:
    explicit SendingModel(Core::IEventBroker *eventBroker, QObject *parent = nullptr);
    ~SendingModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void triggerSend(int row);
    void toggleCyclicMode(int row, bool isActive);

   private:
    IEventBroker *m_eventBroker;

    struct MessageConfig {
        uint32_t canId;
        std::vector<uint8_t> data;
        int cycleTimeMs;
        bool isCyclicActive;
        bool isDbcBased;
        QTimer *timer = nullptr;
    };
    std::vector<MessageConfig> m_messages;
};
}  // namespace Sending
#endif  // SENDINGMODEL_H