#ifndef LOGGINGVIEW_H
#define LOGGINGVIEW_H

#include <QWidget>

#include "logging/model/logging_model.hpp"
#include "core/interface/i_event_broker.hpp"

namespace Logging {
class LoggingView : public QWidget
{
    Q_OBJECT

   public:
    explicit LoggingView(IEventBroker *broker, QWidget *parent = nullptr);
    ~LoggingView();

   private slots:

    void on_btnExport_clicked();
    void on_btnClear_clicked();  // optional clear button

   private:
    Logging::LoggingView *ui;
    LoggingModel *m_model;
};
}  // namespace Logging
#endif  // LOGGINGVIEW_H