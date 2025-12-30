//
// Created by Adrian Rupp on 29.12.25.
//
#pragma once

#include <QWidget>
#include <QTableView>
#include <QTreeView>
#include <QLineEdit>
#include <QComboBox> // Added for the filter box

namespace Dbc {

/**
 * @class SearchableFilterTable
 * @brief Combines a TableView with a Search Bar and a Filter ComboBox on top.
 *
 * Layout:
 * [ Search Bar ......... ] [ Filter Combo ]
 * [ Table View                            ]
 * [ ...                                   ]
 */
class SearchableFilterTable : public QWidget
{
    Q_OBJECT
public:
    explicit SearchableFilterTable(QWidget* parent = nullptr);

    /**
     * @brief Returns the internal table view.
     */
    [[nodiscard]] auto getTableView() const -> QTableView*;

    /**
     * @brief Returns the search line edit (e.g. to set placeholder text).
     */
    [[nodiscard]] auto getSearchBar() const -> QLineEdit*;

    /**
     * @brief Returns the filter combo box (e.g. to add filter options).
     */
    [[nodiscard]] auto getFilterCombo() const -> QComboBox*;

signals:
    /**
     * @brief Emitted when the text in the search bar changes.
     */
    void searchTextChanged(const QString& text);

    /**
     * @brief Emitted when the selection in the filter combo box changes.
     */
    void filterIndexChanged(int index);

private:
    QTableView* m_tableView;
    QLineEdit* m_searchBar;
    QComboBox* m_filterCombo;
};

/**
 * @class SearchableFilterTree
 * @brief Combines a TreeView with a Search Bar and a Filter ComboBox on top.
 *
 * Layout:
 * [ Search Bar ......... ] [ Filter Combo ]
 * [ Tree View                             ]
 * [ ...                                   ]
 */
class SearchableFilterTree : public QWidget
{
    Q_OBJECT

public:
    explicit SearchableFilterTree(QWidget* parent = nullptr);

    /**
     * @brief Returns the internal tree view.
     */
    [[nodiscard]] auto getTreeView() const -> QTreeView*;

    /**
     * @brief Returns the search line edit.
     */
    [[nodiscard]] auto getSearchBar() const -> QLineEdit*;

    /**
     * @brief Returns the filter combo box.
     */
    [[nodiscard]] auto getFilterCombo() const -> QComboBox*;

signals:
    /**
     * @brief Emitted when the text in the search bar changes.
     */
    void searchTextChanged(const QString& text);

    /**
     * @brief Emitted when the selection in the filter combo box changes.
     */
    void filterIndexChanged(int index);

private:
    QTreeView* m_treeView;
    QLineEdit* m_searchBar;
    QComboBox* m_filterCombo; // New Filter Box
};

} // namespace Dbc
