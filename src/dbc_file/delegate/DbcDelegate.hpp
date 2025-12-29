//
// Created by Adrian Rupp on 29.12.25.
//
#pragma once

#include <QStyledItemDelegate>

namespace Dbc {
/**
 * @class DbcDelegate
 * @brief The delegate for the DBC component. Responsible for formatting text and editor panels.
 */
class DbcDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit DbcDelegate(QObject* parent = nullptr);

    // Renders Hex values (0x1A) and appends units
    [[nodiscard]] auto displayText(const QVariant& value, const QLocale& locale) const -> QString override;

    // Creates editors (QSpinBox, etc.) for optional editing
    auto createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const ->QWidget* override;

    // Transfer data between editor and model
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
};

} // namespace CanBusManager::Dbc
