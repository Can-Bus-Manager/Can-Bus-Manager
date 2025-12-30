//
// Created by Adrian Rupp on 29.12.25.
//
#pragma once

#include <QList>
#include <QPersistentModelIndex>
#include <QSortFilterProxyModel>

// Required for DbcItemType enum
#include "core/enum/dbc_itemtype.hpp"

namespace Dbc {

/**
 * @brief A proxy model that flattens a hierarchical tree structure into a linear list.
 *
 * USE CASE:
 * Used for the "Overview" lists and the "All Messages"/"All Signals" tables.
 *
 * CAPABILITIES:
 * 1. Flattening: Recursively collects items of a specific type.
 * 2. Search: Filters by text (Search Bar).
 * 3. Categorization: Filters by specific attributes (Filter Box), e.g., "Sending ECUs".
 */
class FlatListProxy : public QAbstractProxyModel {
    Q_OBJECT

public:
    /**
     * @brief Constructs the FlatListProxy.
     * @param targetType The specific item type to collect (e.g., DbcItemType::Message).
     * @param parent The parent QObject.
     */
    explicit FlatListProxy(Core::DbcItemType targetType, QObject* parent = nullptr);
    ~FlatListProxy() override = default;

    /**
     * @brief Updates the search filter text (Search Bar).
     * Triggers a re-scan of the tree.
     * @param text The text to search for (case-insensitive) in the item names.
     */
    void setSearchFilter(const QString& text);

    /**
     * @brief Updates the category filter (Filter Box).
     * Triggers a re-scan of the tree.
     *
     * @param index The index selected in the ComboBox (e.g., 0="All", 1="Sending").
     * The interpretation of this index depends on the targetType implementation in scanNode.
     */
    void setFilterCategory(int index);


    // --- QAbstractProxyModel Interface Implementation ---

    [[nodiscard]] auto mapFromSource(const QModelIndex& sourceIndex) const -> QModelIndex override;
    [[nodiscard]] auto mapToSource(const QModelIndex& proxyIndex) const -> QModelIndex override;

    [[nodiscard]] auto index(int row, int column, const QModelIndex& parent = QModelIndex()) const -> QModelIndex override;
    [[nodiscard]] auto parent(const QModelIndex& child) const -> QModelIndex override;

    [[nodiscard]] auto rowCount(const QModelIndex& parent = QModelIndex()) const -> int override;
    [[nodiscard]] auto columnCount(const QModelIndex& parent = QModelIndex()) const -> int override;

    void setSourceModel(QAbstractItemModel* sourceModel) override;

public slots:
    /**
     * @brief Scans the source tree and rebuilds the internal index mapping.
     * Called automatically when model changes, search text changes, or category changes.
     */
    void rebuildMapping();

private:
    /**
     * @brief Recursive helper to traverse the source tree.
     * Checks m_filterText AND m_filterCategory to decide inclusion.
     */
    void scanNode(const QModelIndex& parent);

    /** @brief The type of items this proxy should display (e.g., Message). */
    Core::DbcItemType m_targetType;

    /** @brief The current search filter string. */
    QString m_filterText;

    /** @brief The current filter category index (0 = All). */
    int m_filterCategory;

    /**
     * @brief The core mapping structure.
     */
    QList<QPersistentModelIndex> m_mapping;
};

/**
 * @brief A proxy model that filters a tree structure while preserving hierarchy.
 *
 * USE CASE:
 * Used for the "ECUs" page (Tree View).
 *
 * CAPABILITIES:
 * 1. Hierarchy: Maintains the Root -> ECU -> Message structure.
 * 2. Search: Filters nodes by text (Search Bar).
 * 3. Categorization: Filters nodes by attributes via ComboBox (e.g., "Sending Nodes").
 * 4. Cleanup: Automatically hides the "Overview" metadata row.
 */
class TreeFilterProxy : public QSortFilterProxyModel {
    Q_OBJECT

public:
    /**
     * @brief Constructs the TreeFilterProxy.
     * @param parent The parent QObject.
     */
    explicit TreeFilterProxy(QObject* parent = nullptr);
    ~TreeFilterProxy() override = default;
    /**
     * @brief Updates the search filter text.
     * @param text The text to search for (case-insensitive) in the item names.
     */
    void setSearchFilter(const QString& text);

    /**
     * @brief Updates the category filter (Filter Box).
     * @param index The index selected in the ComboBox (e.g., 0="All", 1="Sending Nodes").
     */
    void setFilterCategory(int index);

protected:
    /**
     * @brief Decides whether a row should be included in the model.
     *
     * LOGIC:
     * 1. Hides the "Overview" item (Metadata).
     * 2. Checks if the item matches the Search Text.
     * 3. Checks if the item matches the Filter Category.
     * 4. Uses recursive filtering: If a child matches, the parent is automatically shown.
     */
    [[nodiscard]] auto filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const -> bool override;

private:
    /** @brief The current search filter string. */
    QString m_filterText;

    /** @brief The current filter category index (0 = All). */
    int m_filterCategory;
};

/**
 * @brief A proxy model that restricts the view to the children of a specific node.
 *
 * USE CASE:
 * Used for the "Message Detail View" (Bottom Pane).
 * It displays ALL signals belonging to the currently selected Message.
 *
 * LOGIC:
 * It filters out everything except the direct children (Signals) of the
 * configured parent index (the selected Message). No text or category filtering is applied.
 */
class SingleMessageProxy : public QSortFilterProxyModel {
    Q_OBJECT

public:
    explicit SingleMessageProxy(QObject* parent = nullptr);
    ~SingleMessageProxy() override = default;

    /**
     * @brief Sets the target message whose signals should be displayed.
     * @param parentIndex The model index of the Message in the source model.
     *
     * Calling this triggers an automatic update (invalidate) of the view.
     */
    void setFilterParentIndex(const QModelIndex& parentIndex);

protected:
    /**
     * @brief Decides whether a row should be included.
     *
     * Returns true ONLY if the row's parent matches m_parentIndex.
     */
    [[nodiscard]] auto filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const -> bool override;

private:
    /** @brief The index of the currently selected Message (Source Model). */
    QModelIndex m_parentIndex;
};

} // namespace Dbc