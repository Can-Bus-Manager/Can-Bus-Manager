#pragma once

#include <QAbstractTableModel>
#include <QDateTime>
#include <QString>
#include <map>
#include <vector>

namespace Logging {

/** * @struct LogEntry
 * @brief Represents a single captured CAN frame or decoded message.
 */
struct LogEntry {
    uint32_t messageId;
    QString timestamp;

    /** @brief Decoded signal values (DBC mode). Example: {"EngineTemp": 90.5} */
    std::map<std::string, double> signalValues;
    /** @brief Raw hex bytes (Raw mode). */
    std::vector<uint8_t> rawData;
};

/** * @struct LogSession
 * @brief Represents a complete recording period with metadata and captured data.
 */
struct LogSession {
    QString id;
    QDateTime startDateTime;
    QString duration;
    bool isRecording = false;
    std::vector<LogEntry> entries;
};

/**
 * @class LoggingModel
 * @brief The central data authority for the Logging module.
 * * @details
 * This model manages the lifecycle of logging sessions. It acts as a, list and data provider.
 */
class LoggingModel final : public QAbstractTableModel
{
    Q_OBJECT

   public:
    /**
     * @enum Roles
     * @brief Custom roles for accessing session-specific data.
     */
    enum Roles { SessionIdRole = Qt::UserRole + 1, SessionDataRole, IsActiveRole, EntryCountRole };

    explicit LoggingModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    /**
     * @brief Creates a new session and sets it as the active target for data.
     * @param deviceName The hardware interface used for this session.
     */
    void startNewSession(const QString& deviceName);

    /**
     * @brief Finalizes the active session, locking it for export.
     */
    void stopActiveSession();

    /**
     * @brief Appends data to the current recording.
     * @param entry The captured CAN data or decoded signals.
     */
    void appendEntry(const LogEntry& entry);

    /**
     * @brief Fetches a session by its unique ID.
     */
    const LogSession* getSession(const QString& sessionId) const;

    /**
     * @brief Helper to get the session ID from a View index.
     */
    QString sessionIdAt(const QModelIndex& index) const;

   private:
    /** @brief Updates the duration string of the active session based on current time. */
    void updateActiveDuration();

    std::vector<LogSession> m_sessions;
    int m_activeSessionIndex = -1;

    enum Columns { Col_ID = 0, Col_StartTime, Col_Duration, Col_Count, Col_MAX };
};

}  // namespace Logging