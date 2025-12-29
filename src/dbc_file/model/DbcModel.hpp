//
// Created by Adrian Rupp on 25.12.25.
//

#pragma once

#include <qobjectdefs.h>

#include <QAbstractItemModel>

#include "DbcItem.hpp"
#include "core/dto/DbcDtos.hpp"
#include "core/event/dbc_event.hpp"

class DbcDto;
class IEventBroker;
namespace Dbc {
/**
 * @class DbcModel
 * @brief Stores the data parsed from dbc file. Feeds information to view and delegate.
 *
 */
class DbcModel : public QAbstractItemModel
{
    Q_OBJECT
public:

    explicit DbcModel(IEventBroker& broker, QObject* parent = nullptr);
    ~DbcModel() override;


    //Qt Model interface

    //creates an index for given coordinates
    [[nodiscard]] auto index(int row, int column, const QModelIndex& parent) const -> QModelIndex override;

    //returns value at given index
    [[nodiscard]] auto data(const QModelIndex& index, int role) const -> QVariant override;

    //finds parent of element of given index
    [[nodiscard]] auto parent(const QModelIndex& child) const -> QModelIndex override;

    //returns amount of children of element with given index
    [[nodiscard]] auto rowCount(const QModelIndex& parent) const -> int override;

    //returns amount of attributes/single data values of element with given index
    [[nodiscard]] auto columnCount(const QModelIndex& parent) const -> int override;


    [[nodiscard]] auto headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const -> QVariant override;

    /**
     * @brief Get type of item (Ecu,Message...) of item at given index
     * @param index Index of item to check
     * @return Type of item
     */
    [[nodiscard]] auto getItemType(const QModelIndex& index) const -> Core::DbcItemType;


private:
    /**
     * @brief Resets current model, sets up new data and notifies the View.
     * @param event The triggering DbcParsedEvent.
     */
    void onDbcParsed(const Core::DBCParsedEvent& event);


     /**
      * @brief Resets the current model by clearing the current data tree.
      */
     void resetModel();


    /**
     * @brief Builds internal Tree Structure
     * @param data Dto containing the parsed dbc data
     */
    void setUpData(const Core::DbcConfig& data);

    IEventBroker& m_broker;
    std::unique_ptr<DbcItem> m_rootItem;
};
}