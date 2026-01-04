#pragma once

#include <QListView>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QStackedWidget>
#include <QString>
#include <QStringList>
#include <QWidget>
#include <memory>

namespace Logging {

/**
 * @class LoggingView
 * @brief The main container for the Logging Tab (Composite View).
 *
 * @details
 * **RESPONSIBILITIES:**
 * 1. **Layout:** Manages the Sidebar navigation and the central Page Stack
 *    (Load, Overview, ECUs, Messages, Signals).
 * 2. **Data Wiring:** Owns the Proxy Models, connects them to the Source Model,
 *    and injects them into the specific Pages.
 * 3. **Interaction Logic:** Connects Search Bars, Filter Combos, and Selection Signals
 *    from the Pages to the corresponding Proxies.
 */
class LoggingView : public QWidget
{
    Q_OBJECT

   public:
    explicit LoggingView(IEventBroker* broker, QWidget* parent = nullptr);
    explicit LoggingView(QWidget* parent = nullptr);
    ~LoggingView() override;

    /**
     * @brief Initializes the view with the source data.
     *
     * @caller LoggingComponent::onSignalLogged().
     * @caller LoggingComponent::onLoggingError().
     *
     * @param model The raw LoggingModel containing the data tree.
     */
    void setSourceModel(QAbstractItemModel* model);

    /**
     * @brief Sets the formatting delegate for tables.
     *
     * @caller LoggingComponent (Constructor).
     *
     * @details
     * Applies the `LoggingDelegate` to the Messages Master Table and the Signals Table
     * to ensure Hex values and Units are displayed correctly.
     */
    void setDataItemDelegate(QAbstractItemDelegate* delegate);

    /**
     * @brief Unlocks navigation (Sidebar) after the logging source is ready.
     *
     * @caller LoggingComponent::onLoggingStarted().
     */
    void setNavigationEnabled(bool enabled);

   signals:
    // --- Export & Logging Actions ---
    /**
     * @brief Signal: Emitted when the user requests to export the log data.
     * @caller on_btnExport_clicked().
     */
    void exportRequested();

    /**
     * @brief Signal: Emitted when the user requests to start a live preview.
     * @caller UI.
     */
    void startPreviewRequested();

    /**
     * @brief Signal: Emitted when the user requests to start logging.
     */
    void startLoggingRequested();

    /**
     * @brief Signal: Emitted when the user requests to pause logging.
     */
    void pauseLogging();

    /**
     * @brief Signal: Emitted when the user requests to pause logging (requested variant).
     */
    void pauseLoggingRequested();

    /**
     * @brief Resume logging.
     */
    void resumeLoggingRequested();

    /**
     * @brief Signal: Emitted when the user requests to stop logging.
     */
    void stopLogging();

    /**
     * @brief Misc logging UI actions.
     */
    void editSettingsRequested();

    // --- Mode & Interface Selection ---
    void modeSelected(int mode);  // e.g., 0 for Raw, 1 for DBC
    void interfaceChanged(const QString& interfaceName);
    void dbcFileSelected(const QString& filePath);

    // --- DBC Specific Actions ---
    void ecuVisibilityChanged(const QString& ecuName, bool visible);
    void changeDbcFileRequested();

    // --- Export Actions ---
    void exportPathEntered(const QString& path);
    void retryExportRequested();
    void exportProcessFinished();

   private slots:
    /**
     * @brief Handles sidebar navigation to switch the active page in the stack.
     * @caller Sidebar QListView (clicked signal).
     */
    void onSidebarSelectionChanged(const QModelIndex& index);

    // Button actions from UI
    void on_btnExport_clicked();
    void on_btnClear_clicked();

    // --- State & UI Control ---
    void setIdleState();
    void setRawModeLayout();
    void setDbcModeLayout();
    void setLoggingActive(bool active);
    void updateSignalPreview(const QString& data);
    void showErrorMessage(const QString& message);

    // --- Export Management ---
    void openFileSelectionDialog();
    void updateExportStatus(const QString& status);

   public slots:
    // Slots to handle internal UI logic or feedback from Controller
    void onIncomingSignal(const QString& signalData);
    void onConversionStatusChanged(bool successful);

   private:
    // --- Member Variables (UI Components & State) ---

    // Helper setup methods
    void setupUi();
    void createSubViews();
    void setupConnections();

    // UI Layout state
    enum class ViewState { Idle, RawConfig, DbcConfig, Logging, Exporting };
    ViewState m_currentState;

    // Input Data
    QString m_selectedInterface;
    QString m_currentDbcPath;
    QString m_exportPath;

    // Configuration Lists
    QStringList m_availableInterfaces;
    QStringList m_parsedEcus;

    // UI containers
    QListView* m_sidebarList = nullptr;
    QStackedWidget* m_contentStack = nullptr;

    // Proxy models and delegates
    std::unique_ptr<QSortFilterProxyModel> m_messageFilterProxy;
    std::unique_ptr<QSortFilterProxyModel> m_signalFilterProxy;
    std::unique_ptr<QAbstractItemDelegate> m_delegate;

    // Qt UI Elements (Placeholders for actual Widgets)
    QPushButton* m_startLoggingBtn;
    QPushButton* m_pauseLoggingBtn;
    QPushButton* m_stopLoggingBtn;
    QPushButton* m_exportBtn;
};
}  // namespace Logging
