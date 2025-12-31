#pragma once

#include <QAbstractItemDelegate>

namespace AppRoot {

/**
 * @class AppRootDelegate
 * @brief Custom painter for the AppRootView shell.
 * @details
 * Handles the visual presentation of the TabBar and the Shell's background,
 * allowing for custom styling decoupled from the View's layout logic.
 */
class AppRootDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
   public:
    explicit AppRootDelegate(QObject* parent = nullptr);
    ~AppRootDelegate() override = default;

    /** @brief Renders the UI elements for a given model index. */
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override;

    /** @brief Returns the size required for the rendered elements. */
    [[nodiscard]] auto sizeHint(const QStyleOptionViewItem& option,
                                const QModelIndex& index) const -> QSize override;
};

}  // namespace AppRoot
