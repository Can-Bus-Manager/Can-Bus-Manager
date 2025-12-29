//
// Created by Adrian Rupp on 24.12.25.
//

#pragma once
#include <qvariant.h>
#include "core/enum/DbcItemType.hpp"

namespace Dbc {
/**
 * @class DbcItem
 * @brief Represents a node in the DBC-Tree held by the model.
 */
class DbcItem
{
public:
    explicit DbcItem(Core::DbcItemType type, DbcItem* parent = nullptr);
    ~DbcItem();

    //Tree navigation
    void appendChild(std::unique_ptr<DbcItem> child);
    [[nodiscard]] auto childAt(int row) const -> DbcItem*;
    [[nodiscard]] auto childCount() const -> int;
    [[nodiscard]] auto columnCount() const -> int;
    [[nodiscard]] auto data(int column) const -> QVariant;
    [[nodiscard]] auto row() const -> int;
    [[nodiscard]] auto parent() const -> DbcItem*;
    [[nodiscard]] auto type() const -> Core::DbcItemType;

private:
    Core::DbcItemType m_type; //type of item (ecu, message, signal, root)
    std::vector<std::unique_ptr<DbcItem>> m_children; //list of children-items
    DbcItem* m_parent; //parent item
    QList<QVariant> m_data; //values like name, ID, dlc, offset, scale...
};
};
