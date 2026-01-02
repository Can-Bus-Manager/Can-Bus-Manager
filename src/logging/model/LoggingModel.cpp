#include "LoggingModel.hpp"
#include <QDateTime>

LoggingModel::LoggingModel(IEventBroker* broker, QObject* parent)
    : QAbstractTableModel(parent), m_broker(broker) {
    /*
     * The constructor establishes the connection to the data source.
     * 1. Subscription:
     * It uses the IEventBroker to listen for incoming CAN messages. 
     * 2. Data Mapping:
     * When a message is received, a callback or lambda function captures the 
     * raw data (ID, Payload) and encapsulates it into a 'LogEntry' structure, 
     * adding metadata like a high-resolution timestamp.
     */
}

int LoggingModel::rowCount(const QModelIndex &parent) const {
    /*
     * Returns the current number of log entries stored in the internal container.
     * This tells the QTableView how many rows it needs to render.
     */
    return 0; // Placeholder
}

int LoggingModel::columnCount(const QModelIndex &parent) const {
    /*
     * Defines the horizontal structure of the log. Includes:
     * Column 0: Timestamp (hh:mm:ss.zzz)
     * Column 1: Direction (RX/TX)
     * Column 2: CAN ID (Hexadecimal)
     * Column 3: Data Payload (Hex bytes)
     */
    return 4;
}

void LoggingModel::appendLogEntry(const LogEntry& entry) {
    //appends a new log entry to m_logs and notifies views:
    /*
     * 1. Synchronization:
     * It must call 'beginInsertRows' to notify the View that the model 
     * structure is about to change.
     * 2. Storage:
     * Adds the new entry to the internal std::vector or list.
     * 3. Finalization:
     * Calls 'endInsertRows' so the View can refresh and show the new message.
     */
}

QVariant LoggingModel::data(const QModelIndex &index, int role) const {
    /*
     * This is the primary method for providing data to the View.
     * 1. Role Check:
     * It primarily handles 'Qt::DisplayRole' to return text for the cells.
     * 2. Formatting:
     * - Timestamps are formatted as strings.
     * - CAN IDs are converted to uppercase Hex strings with a "0x" prefix.
     * - The Payload (vector of bytes) is converted into a space-separated 
     * string of Hex pairs (e.g., "DE AD BE EF").
     */
    return QVariant();
}

void LoggingModel::clearLogs() {
    /*
     * Resets the entire log history.
     * 1. Notification:
     * Uses 'beginResetModel' because every single row is being removed.
     * 2. Memory Management:
     * Clears the internal container to free up memory.
     * 3. Completion:
     * Uses 'endResetModel' to inform the View that the table is now empty.
     */
}