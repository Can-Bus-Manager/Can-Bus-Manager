//
// Created by Adrian Rupp on 24.12.25.
//
#pragma once
#include <QList>
#include <QVariant>
#include <memory>
#include <vector>
#include "core/enum/dbc_itemtype.hpp"

namespace Dbc {

/**
 * @class dbc_item
 * @brief Represents a single node in the DBC-Tree structure.
 * Nodes have types as defined ind Core::DbcItemType
 * A node holds a set of children notes (Root: ECU nodes and one Overview node; ECU: Message nodes;
 * Messages: Signal nodes), several data items (e.g. for messages: Name, ID, Dlc,...) and a pointer
 * to its parent node
 */
class dbc_item
{
public:
    /**
     * @brief Constructs a new item.
     * @param data The column data for this item (Name, Value, Unit, etc.).
     * @param type The semantic type (ECU, Message, Signal, Root, Overview).
     * @param parent The parent item (nullptr for root).
     */
    explicit dbc_item(const QList<QVariant>& data, Core::DbcItemType type, dbc_item* parent = nullptr);
    ~dbc_item() = default;

//-- Tree navigation methods--

    void appendChild(std::unique_ptr<dbc_item> child);

    [[nodiscard]] auto childAt(int row) const -> dbc_item*;
    [[nodiscard]] auto childCount() const -> int;
    [[nodiscard]] auto columnCount() const -> int;

    // Data Access
    [[nodiscard]] auto data(int column) const -> QVariant;

    // Metadata Access
    [[nodiscard]] auto row() const -> int;
    [[nodiscard]] auto parent() const -> dbc_item*;
    [[nodiscard]] auto type() const -> Core::DbcItemType;

private:
    Core::DbcItemType m_type;
    std::vector<std::unique_ptr<dbc_item>> m_children;
    dbc_item* m_parent;

    // Holds the displayable data for columns.
    // E.g. for Signal: [Name, StartBit, Length, Factor, Offset, Min, Max, Unit, Receiver...]
    QList<QVariant> m_data;
};

} // namespace Dbc
