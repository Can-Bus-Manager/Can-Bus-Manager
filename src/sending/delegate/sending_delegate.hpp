#pragma once

#include <QObject>
#include <QStyledItemDelegate>

namespace Sending {

/**
 * @class SendingDelegate
 * @brief The active controller for the Sending module.
 * * Owns the transmission logic, including the cyclic timer. It bridges
 * the passive Model/View to the Component's broker slots.
 */
class SendingDelegate final : public QStyledItemDelegate
{
    Q_OBJECT

   public:
    explicit SendingDelegate(QObject* parent = nullptr);
    ~SendingDelegate() override = default;

    /** @brief Painting the CAN message card manually for high performance */
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override;

    /** @brief Creating the editor (e.g., the SpinBoxes for signal values) */
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;

    /**
     * @brief Writes data from the editor back to the Model.
     */
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const override;
};

}  // namespace Sending