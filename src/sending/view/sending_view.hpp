
#ifndef SENDINGVIEW_HPP
#define SENDINGVIEW_HPP
#include <QWidget>

#include "core/interface/i_event_broker.hpp"
#include "sending/delegate/sending_delegate.hpp"
#include "sending/model/sending_model.hpp"

namespace Sending {

class SendingView : public QWidget
{
    Q_OBJECT

   public:
    explicit SendingView(Core::IEventBroker *broker, QWidget *parent = nullptr);
    ~SendingView();

   private slots:
    // Slots to handle button clicks from the UI
    void on_btnSendMessage_clicked();
    void on_btnToggleCyclic_clicked();

   private:
    Sending::SendingView *ui;
    SendingModel *m_model;        // data source
    SendingDelegate *m_delegate;  // custom editor
};
}  // namespace Sending
#endif  // SENDINGVIEW_HPP