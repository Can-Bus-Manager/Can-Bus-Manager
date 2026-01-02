#include "LoggingView.hpp"
#include "ui_LoggingView.hpp"

LoggingView::LoggingView(IEventBroker* broker, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoggingView)
{
    ui->setupUi(this);

    /*
     * 1. Model Initialization:
     * We instantiate the LoggingModel and pass the IEventBroker. 
     * This establishes the path from the CAN hardware/broker directly 
     * into our data structure.
     */
    m_model = new LoggingModel(broker, this);

    /*
     * 2. View Connection:
     * We link the QTableView (from the UI file) to our model. 
     * The view now knows where to fetch the rows and columns to display.
     */
    ui->tableView->setModel(m_model);

    /*
     * 3. UX - Automatic Scrolling:
     * This is a critical feature for a live log. We connect to a signal 
     * that fires whenever new rows are inserted into the model. 
     * Inside the handler, we tell the table to scroll to the bottom 
     * so the user always sees the most recent CAN traffic.
     */

    /*
     * 4. Visual Layout:
     * Here we configure how the table columns behave. For example, 
     * we can set the "Payload" column to stretch and fill the remaining 
     * window space, or adjust header resizing modes for better readability.
     */
}

LoggingView::~LoggingView() {
    /*
     * Standard cleanup for the UI pointer to prevent memory leaks.
     */
    delete ui;
}

void LoggingView::on_btnClear_clicked() {
    /*
     * This slot is triggered when the user clicks the "Clear" button.
     * It calls the clear method in the model to wipe the history. 
     * The View will automatically refresh and appear empty as a result.
     */
}