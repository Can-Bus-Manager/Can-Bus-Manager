#include <QWidget>
#include "SendingModel.h"
#include "SendingDelegate.h"

namespace sending {

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
    Ui::SendingView *ui;
    SendingModel *m_model;        //data source
    SendingDelegate *m_delegate;  //custom editor
};
}
#endif