#include "SendingView.hpp"
#include "ui_SendingView.hpp"

SendingView::SendingView(IEventBroker* broker, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SendingView)
{
    ui->setupUi(this);

    m_model = new SendingModel(broker, this);
    m_delegate = new SendingDelegate(broker, this);

    ui->tableView->setModel(m_model);

    ui->tableView->setItemDelegate(m_delegate);
    
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

SendingView::~SendingView() {
    delete ui;
}

void SendingView::on_btnSendMessage_clicked() {
    QModelIndex currentIndex = ui->tableView->currentIndex();
    if (currentIndex.isValid()) {
        m_model->sendMessage(currentIndex.row());
    }
}

void SendingView::on_btnToggleCyclic_clicked() {
    QModelIndex currentIndex = ui->tableView->currentIndex();
    if (currentIndex.isValid()) {
        m_model->toggleCyclic(currentIndex.row());
    }
}

//methods to add and remove mesages?