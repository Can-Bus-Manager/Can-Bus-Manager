#ifndef LOGGINGVIEW_H
#define LOGGINGVIEW_H

#include <QWidget>
#include "LoggingModel.h"

namespace Ui {
class LoggingView;
}

class LoggingView : public QWidget {
    Q_OBJECT

public:
    explicit LoggingView(IEventBroker* broker, QWidget *parent = nullptr);
    ~LoggingView();

private slots:

    void on_btnExport_clicked();//link to sending tab?
    void on_btnClear_clicked();//optional clear button

private:
    Ui::LoggingView *ui;
    LoggingModel *m_model;
};

#endif // LOGGINGVIEW_H