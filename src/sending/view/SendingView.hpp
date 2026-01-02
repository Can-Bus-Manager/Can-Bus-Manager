
#ifndef SENDINGVIEW_HPP
#define SENDINGVIEW_HPP
#include <QWidget>
#include "core/interface/i_event_broker.hpp"
#include "sending/model/SendingModel.hpp"
#include "sending/delegate/SendingDelegate.hpp"

namespace Sending {

class SendingView : public QWidget {
    Q_OBJECT

public:
    explicit SendingView(IEventBroker* broker, QWidget *parent = nullptr);
    ~SendingView();

private slots:
    // Slots to handle button clicks from the UI
    void on_btnSendMessage_clicked();
    void on_btnToggleCyclic_clicked();
    
private:
    Sending::SendingView *ui;
    SendingModel *m_model;        //data source
    SendingDelegate *m_delegate;  //custom editor
};
}
#endif // SENDINGVIEW_HPP