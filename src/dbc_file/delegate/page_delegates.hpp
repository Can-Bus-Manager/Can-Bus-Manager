//
// Created by Adrian Rupp on 30.12.25.
//
#pragma once

#include <QStyledItemDelegate>
#include <QTreeView>
#include <QPainter>
#include <QEvent>
#include "core/enum/dbc_itemtype.hpp"

namespace Dbc {

/**
 * @brief A custom delegate to render the list items (in ECUs and Messages overviews) in the Overview Page.
 *
 * It draws items as "Cards" containing:
 * - A rounded border background.
 * - An icon on the left.
 * - The name text.
 * - A badge (gray box with count) on the right.
 */
class OverviewListsDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit OverviewListsDelegate(QObject* parent = nullptr);

    /**
     * @brief Renders the card visualization of the list items.
     */
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    /**
     * @brief Defines the fixed size for each card in the grid.
     */
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};



/**
 * @brief Custom delegate to render the ECU Hierarchy as expandable "Cards" for the Ecus page.
 *
 * Card design hierarchy:
 * - **ECU (Level 0):** Large Card, Icon, Name, Message Count Badge, Expansion Arrow on the right.
 * - **Message (Level 1):** Header-like row, Name, ID Badge, Signals Count Badge.
 * - **Signal (Level 2):** Detail row, Name, Value Range, Unit Badge.
 *
 * Interaction:
 * - Handles mouse clicks on the right-aligned expansion arrow to toggle the TreeView state.
 */
class EcuTreeDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    /**
     * @brief Constructs the delegate.
     * @param view Pointer to the specific TreeView (needed to control expansion state).
     * @param parent Parent object.
     */
    explicit EcuTreeDelegate(QTreeView* view, QObject* parent = nullptr);

    /**
     * @brief Renders the item content based on its DbcItemType.
     */
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    /**
     * @brief Calculates the height of the rows (ECUs are taller than Signals).
     */
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    /**
     * @brief Handles user interactions (specifically clicking the expand arrow).
     * Replaces standard TreeView expansion logic for the right-aligned arrow.
     */
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

private:
    /**
     * @brief Helper to calculate the exact geometry of the expansion arrow/chevron.
     * Used in both paint() (to draw) and editorEvent() (to detect clicks).
     */
    QRect getExpandButtonRect(const QRect& itemRect) const;

    // --- Painting Helpers ---
    void paintEcuCard(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void paintMessageRow(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void paintSignalRow(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

    /**
     * @brief Draws a rounded badge with text (e.g., "rpm" or "0x120").
     */
    void drawBadge(QPainter* painter, const QRect& rect, const QString& text, const QColor& bg, const QColor& fg) const;

    QTreeView* m_treeView; // Reference to control expand/collapse
};

/**
 * @brief Renders the detailed Signal cards in the Message Detail View (Bottom Pane).
 *
 * VISUALS:
 * - Draws a container with a rounded border.
 * - **Header:** Signal Name (Bold) + Unit Badge (gray box, right aligned).
 * - **Grid Layout:** Renders attributes like Start Bit, Length, Factor, Offset, Min, Max
 *   in a structured grid layout within the card.
 * - **Footer:** Receiver Node.
 */
class MessagesSignalCardDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit MessagesSignalCardDelegate(QObject* parent = nullptr);
    ~MessagesSignalCardDelegate() override = default;

    /**
     * @brief Renders the complete card visualization.
     *
     * Uses QPainter to draw:
     * 1. A rounded rectangle border (The Card).
     * 2. The Header section (Name & Unit).
     * 3. A 2x4 or 4x2 grid for the numeric attributes.
     * 4. The Footer section.
     */
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    /**
     * @brief Defines the size of the card.
     *
     * Calculates a fixed height sufficient to display the Header,
     * the Grid of attributes, and the Footer (approx. 120-150px based on design).
     */
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

private:
    /**
     * @brief Helper to draw a text label with a value below it (for the grid).
     * e.g. "Start Bit" (gray) -> "0" (black).
     */
    void drawGridItem(QPainter* painter, const QRect& rect, const QString& label, const QString& value) const;

    /**
     * @brief Helper to draw a rounded badge (used for the Unit).
     */
    void drawBadge(QPainter* painter, const QRect& rect, const QString& text) const;
};

/**
 * @brief Custom delegate for the global Signals Table (SRS 6.5).
 *
 * VISUALS:
 * - **Standard Columns:** Renders text normally (Name, Unit, etc.).
 * - **Message Column:** Renders a composite view:
 *   [ ID Badge (Gray) ]  [ Message Name ]
 * - **Formatting:** Can handle conditional formatting (e.g. adding "Bit" to length,
 *   formatting range as "[min, max]").
 */
class SignalTableDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit SignalTableDelegate(QObject* parent = nullptr);
    ~SignalTableDelegate() override = default;

    /**
     * @brief Renders the cells.
     * Special handling for the "Message" column to draw the ID badge.
     */
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    /**
     * @brief Returns size hint.
     * Ensures rows are tall enough for the badges.
     */
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

} // namespace Dbc
