#ifndef LOGGINGMODEL_H
#define LOGGINGMODEL_H

#include <QAbstractTableModel>
#include <vector>

#include "core/interface/i_event_broker.hpp"

namespace Logging {

struct LogEntry {
    QString timestamp;
    uint32_t canId;
    QString direction;  // "RX" or "TX"
    std::vector<uint8_t> data;
};

class LoggingModel : public QAbstractTableModel
{
    Q_OBJECT

   public:
    explicit LoggingModel(Core::IEventBroker* broker, QObject* parent = nullptr);

    // Standard TableModel overrides
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // method to handle new incoming events
    void appendLogEntry(const LogEntry& entry);

   private:
    Core::IEventBroker* m_broker;
    std::vector<LogEntry> m_logs;  // history of messages
};
}  // namespace Logging
#endif  // LOGGINGMODEL_H