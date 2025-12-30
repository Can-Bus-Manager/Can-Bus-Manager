//
// Created by Adrian Rupp on 25.12.25.
//

#pragma once

#include <QAbstractItemModel>
#include <memory>

#include "core/interface/i_event_broker.hpp" // Connection definition is here
#include "core/event/dbc_event.hpp"
#include "dbc_item.hpp"
#include "dbc_roles.hpp" // Include definitions of custom roles

namespace Dbc {

/**
 * @class DbcModel
 * @brief Stores the data parsed from dbc file in a tree structure.
 *
 * Acts as a "Smart Model" by subscribing to the EventBroker directly.
 * Maps Custom Roles (DbcRoles) to the internal data of dbc_items.
 */
class DbcModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DbcModel(Core::IEventBroker& broker, QObject* parent = nullptr);
    ~DbcModel() override;

    // --- Qt Model Interface ---
    [[nodiscard]] auto index(int row, int column, const QModelIndex& parent) const -> QModelIndex override;
    [[nodiscard]] auto parent(const QModelIndex& child) const -> QModelIndex override;
    [[nodiscard]] auto rowCount(const QModelIndex& parent) const -> int override;
    [[nodiscard]] auto columnCount(const QModelIndex& parent) const -> int override;

    /**
     * @brief Returns data for a specific index and role.
     *
     * Handles mapping of DbcRoles (e.g. Role_Unit) to the correct column
     * in the internal dbc_item data list.
     */
    [[nodiscard]] auto data(const QModelIndex& index, int role) const -> QVariant override;

    [[nodiscard]] auto headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const -> QVariant override;

    // --- Helper ---
    [[nodiscard]] auto getItemType(const QModelIndex& index) const -> Core::DbcItemType;

private:
    // Event Callback
    void onDbcParsed(const Core::DBCParsedEvent& event);

    void setupData(const Core::DbcConfig& data);

    Core::IEventBroker& m_broker;

    // CRITICAL: Keeps the event subscription alive.
    // Without this, the lambda passed to subscribe() is destroyed immediately.
    Core::Connection m_dbcParsedConnection;

    std::unique_ptr<dbc_item> m_rootItem;
};

} // namespace Dbc}