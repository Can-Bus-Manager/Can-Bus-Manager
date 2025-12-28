#pragma once

#include <QAbstractItemModel>

namespace AppRoot {

/**
 * @class AppRootModel
 * @brief Concrete implementation of the AppRoot data model.
 * @details Manages the data structures required for the AppRoot module
 * and provides them via the QAbstractItemModel interface.
 */
class AppRootModel : public QAbstractItemModel
{
    Q_OBJECT
   public:
    explicit AppRootModel(QObject* parent = nullptr);
    ~AppRootModel() override = default;

    // Standard QAbstractItemModel interface overrides...
    [[nodiscard]] auto index(int row, int column, const QModelIndex& parent) const
        -> QModelIndex override;
    [[nodiscard]] auto parent(const QModelIndex& index) const -> QModelIndex override;
    [[nodiscard]] auto rowCount(const QModelIndex& parent) const -> int override;
    [[nodiscard]] auto columnCount(const QModelIndex& parent) const -> int override;
    [[nodiscard]] auto data(const QModelIndex& index, int role) const -> QVariant override;
};

}  // namespace AppRoot