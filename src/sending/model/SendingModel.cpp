#include "SendingModel.hpp"


class SendingModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit SendingModel(IEventBroker* eventBroker, QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void triggerSend(int row);
    void toggleCyclicMode(int row, bool isActive);

private:
    IEventBroker* m_eventBroker;
    std::vector<SendingMessageConfig> m_messages;
};

SendingModel::SendingModel(IEventBroker* broker, QObject* parent)
    : QAbstractTableModel(parent), m_eventBroker(broker) {
    // Initialization
}

void SendingModel::triggerSend(int row) {
    auto &msg = m_messages[row];
    
    auto event = std::make_shared<SendRawEvent>(msg.canId, msg.data);
    
    m_eventBroker->publish(event);
}



void sendMessage(const int row) {
    // Implementation to send the CAN message using m_eventBroker
}

void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    // Implementation to notify views about data changes
}

void SendingModel::toggleCyclicMode(int row, bool isActive) {
    if (row < 0 || row >= static_cast<int>(m_messages.size())) return;

    auto &msg = m_messages[row];
    msg.isCyclicActive = isActive;

    if (isActive) {
        //Create the timer
        if (!msg.timer) {
            msg.timer = new QTimer(this);
            //Connect the timer to our triggerSend function
            connect(msg.timer, &QTimer::timeout, this, [this, row]() {
                sendMessage(row);
            });
        }
        //Set speed and start
        msg.timer->setInterval(msg.cycleTimeMs);
        msg.timer->start();
    } else {
        //Stop timer
        if (msg.timer) {
            msg.timer->stop();
        }
    }

    // Tell the View to update the "Status" column
    QModelIndex index = this->index(row, 3); 
    emit dataChanged(index, index);
}

QVariant SendingModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) 
        return QVariant();

    const auto &msg = m_messages[index.row()];

    if (index.column() == 0) {
        return QString("0x%1").arg(msg.canId, 0, 16); //ID as Hex
    }

    if (index.column() == 1) {
        return QString::fromStdString(bytesToHexString(msg.data)); //payload as Hex
    }

    if (index.column() == 2) {
    return QString("%1 ms").arg(msg.cycleTimeMs);
    }
    if (index.column() == 3) {
        return msg.isCyclicActive ? "Active" : "Inactive";
    }   
    return QVariant();     
}

setData(index, value, role){
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    auto &msg = m_messages[index.row()];

    if (index.column() == 0) {
        bool ok;
        uint32_t canId = value.toString().toUInt(&ok, 16);
        if (ok) {
            msg.canId = canId;
        } else {
            return false;
        }
    } else if (index.column() == 1) {
        std::string dataStr = value.toString().toStdString();
        msg.data = hexStringToBytes(dataStr);
    } else if (index.column() == 2) {
        bool ok;
        int cycleTime = value.toString().remove().toInt(&ok);
        if (ok) {
            msg.cycleTimeMs = cycleTime;
        } else {
            return false;
        }
    } else if (index.column() == 3) {
        msg.isCyclicActive = (value.toString() == "Active");
    } else {
        return false;
    }

    emit dataChanged(index, index);
    return true;
}


