//
// Created by Adrian Rupp on 29.12.25.
//
#pragma once

#include <QStyledItemDelegate>

namespace Dbc {

/**
 * @brief Standard delegate for formatting data in read-only QTableViews.
 *
 * USE CASE:
 * Used in "Messages Page" (Master Table) and "Signals Page".
 *
 * RESPONSIBILITIES:
 * Intercepts the data before painting to apply formatting based on Custom Roles.
 * - Hex Formatting: If Role_IsHex is true.
 * - Unit Suffix: If Role_Unit returns a string.
 */
class DbcDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit DbcDelegate(QObject* parent = nullptr);
    ~DbcDelegate() override = default;

    /**
     * @brief Initializes the style option with formatted text.
     *
     * Checks the model for DbcRoles::Role_IsHex and DbcRoles::Role_Unit.
     * Modifies option text to e.g., "0x123" or "50 km/h".
     */
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override;

    /**
     * @brief Converts raw QVariant data to string (helper for default implementation).
     */
    [[nodiscard]] auto displayText(const QVariant& value, const QLocale& locale) const -> QString override;
};

} // namespace Dbc