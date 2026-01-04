#pragma once

#include <QObject>
#include <QTimer>
#include <string>

#include "core/dto/can_dto.hpp"
#include "sending/model/sending_model.hpp"
#include "sending/view/sending_view.hpp"

namespace Sending {

/**
 * @class SendingDelegate
 * @brief The active controller for the Sending module.
 * * Owns the transmission logic, including the cyclic timer. It bridges
 * the passive Model/View to the Component's broker slots.
 */
class SendingDelegate final : public QObject
{
    Q_OBJECT

   public:
    explicit SendingDelegate(SendingModel* model, SendingView* view, QObject* parent = nullptr);
    ~SendingDelegate() override = default;

   signals:
    /** @brief Signal to Component to publish a Raw message to the Broker */
    void requestSendRaw(const std::string& device, const Core::RawCanMessage& message);

    /** @brief Signal to Component to publish a DBC message to the Broker */
    void requestSendDbc(const std::string& device, const Core::DbcCanMessage& message);

   private slots:
    /** @brief Triggered by View "Send" button or the internal cyclic timer */
    void executeSend();

    /** @brief Monitors Model for changes in Mode, Interval, or Cyclic Enable/Disable */
    void onModelStateChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight,
                             const QVector<int>& roles);

    /** @brief Handles sidebar navigation clicks from the View */
    void onViewModeRequested(bool isDbc);

   private:
    SendingModel* m_model;
    SendingView* m_view;
    QTimer* m_cyclicTimer;
};

}  // namespace Sending