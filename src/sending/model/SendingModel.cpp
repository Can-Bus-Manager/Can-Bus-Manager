

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