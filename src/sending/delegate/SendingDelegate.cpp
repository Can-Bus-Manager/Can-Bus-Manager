class SendingDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit SendingDelegate(IEventBroker* eventBroker, QObject* parent = nullptr);
    // Other delegate methods...
private:
    IEventBroker* m_eventBroker;
};

SendingDelegate::SendingDelegate(IEventBroker* broker, QObject* parent)
    : QStyledItemDelegate(parent), m_eventBroker(broker) {
    // Initialization
}

void SendingDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) {
    // Implementation to set data in the model
}

QWidget* SendingDelegate::createEditor(QWidget *parent, 
                                       const QStyleOptionViewItem &option, 
                                       const QModelIndex &index) const override {
    
}

void SendingDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    // Implementation to set data in the editor widget
}
void SendingDelegate::updateEditorGeometry(QWidget *editor, 
                                          const QStyleOptionViewItem &option, 
                                          const QModelIndex &index) const override {
    editor->setGeometry(option.rect);
}

