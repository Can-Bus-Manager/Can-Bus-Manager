#pragma once

#include <QModelIndex>
#include <QObject>
#include <memory>

#include "logging/model/logging_model.hpp"
#include "logging/view/logging_view.hpp"
#include "logging/view/message_selection_dialog.hpp"

namespace Logging {

/**
 * @class LoggingDelegate
 * @brief The controller logic that bridges the View, Model, and Modal Dialog.
 * * @details
 * It is responisble to route start/stop action, fullfill navigation and style.
 */
class LoggingDelegate final : public QObject
{
    Q_OBJECT

   public:
    /**
     * @brief Constructs the Delegate.
     * @param view Pointer to the composite LoggingView.
     * @param model Pointer to the session-based LoggingModel.
     */
    explicit LoggingDelegate(LoggingView* view, LoggingModel* model, QObject* parent = nullptr);

    /**
     * @brief Renders simulated buttons in the "Actions" column.
     */
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override;

    /**
     * @brief Handles mouse clicks to detect if a "button" was pressed.
     * @details If a button area is clicked, it emits the corresponding signal from the View.
     */
    bool editorEvent(QEvent* event, QAbstractItemModel* model,
                     const QStyleOptionViewItem& option, const QModelIndex& index) override;

   public slots:
    /**
     * @brief Opens the MessageSelectionDialog modal window.
     * @details If Accepted, triggers the Component to start logging via startLoggingRequested().
     */
    void onHandleStartRequest();

    /**
     * @brief Finalizes the active session in the Model and updates the View's state.
     */
    void onHandleStopRequest();

    /**
     * @brief Initiates a file dialog and triggers the CSV export process.
     * @param index The QModelIndex from the View's tree row.
     */
    void onHandleExportRequest(const QModelIndex& index);

    /**
     * @brief Populates a detail widget and commands the View to show its internal overlay.
     * @param index The QModelIndex representing the session to inspect.
     */
    void onHandleDetailRequest(const QModelIndex& index);

   signals:
    /** @brief Signal to the LoggingComponent to begin Broker subscriptions. */
    void startLoggingRequested(const QString& device, const std::vector<uint32_t>& selectedIds);

    /** @brief Signal to the LoggingComponent to release Broker handles. */
    void stopLoggingRequested();

    /** @brief Signal to the LoggingComponent to write data to disk. */
    void exportValidated(const QString& sessionId, const QString& filePath);

   private:
    /**
     * @brief Helper to generate DbcMessageCard widgets for the selection modal.
     * @return A list of message cards in 'Selection' mode.
     */
    void populateSelectionDialog(MessageSelectionDialog* dialog);

    LoggingView* m_view;
    LoggingModel* m_model;
};

}  // namespace Logging