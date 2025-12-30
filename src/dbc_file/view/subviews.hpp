//
// Created by Adrian Rupp on 28.12.25.
//

#pragma once
#include <QLabel>
#include <QSplitter>
#include <QWidget>

#include "searchable_widgets.hpp"

namespace Dbc
{

/**
 * @brief The landing page for the DBC module (SRS 6.1 "Load New").
 *
 * It provides a centered "Card" layout allowing the user to upload a DBC file
 * either by Drag & Drop or by clicking to open a file dialog.
 */
class LoadPage : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructs the LoadPage widget.
     * @param parent The parent widget.
     */
    explicit LoadPage(QWidget* parent = nullptr);
    ~LoadPage() override = default;

    signals:
        /**
         * @brief Emitted when a file is successfully selected by the user.
         *
         * Triggered by either dropping a valid file onto the widget or selecting
         * one via the system file dialog.
         *
         * @param filePath The absolute path to the selected file.
         */
        void fileSelected(const QString& filePath);

protected:
    /**
     * @brief Handles drag enter events to validate dropped data.
     * Updates the UI (e.g., green border) if the dragged item is a dbc file.
     */
    void dragEnterEvent(QDragEnterEvent* event) override;

    /**
     * @brief Handles drop events to extract the file path.
     */
    void dropEvent(QDropEvent* event) override;

    /**
     * @brief Event Filter for the upload Box.
     * Used to detect clicks on the central "Upload Box" frame to trigger the file dialog.
     */
    auto eventFilter(QObject* watched, QEvent* event) -> bool override;

private slots:
    /**
     * @brief Opens a QFileDialog to let the user browse for a DBC file.
     */
    void onBrowseButtonClicked();

private:
    /**
     * @brief Initializes the layout, frames, and styling.
     */
    void setupUi();

    /**
     * @brief The clickable area for file upload.
     * Stored as a member to handle event filtering and visual updates during drag & drop.
     */
    QFrame* m_uploadBoxFrame;
};

/**
 * @brief The Overview page displaying file statistics and summaries (SRS 6.2).
 *
 * Structure:
 * - Section 1: File Metadata (Version, Date).
 * - Section 2: KPI Cards (Counts for ECUs, Messages, Signals).
 * - Section 3: Horizontal flow lists for ECUs and Messages.
 *
 * Uses QDataWidgetMapper for Sections 1 & 2, and QListViews for Section 3.
 */
class OverviewPage : public QWidget {
    Q_OBJECT

public:
    explicit OverviewPage(QWidget* parent = nullptr);
    ~OverviewPage() override = default;

    /**
     * @brief Returns the mapper used to populate the static labels (Top/Middle sections).
     * The View calls this to set the source model and current index.
     */
    [[nodiscard]] auto getMapper() const -> QDataWidgetMapper* { return m_mapper; }

    /**
     * @brief Returns the list view for the ECUs section.
     * The View calls this to set the ECU Proxy Model.
     */
    [[nodiscard]] auto getEcuList() const -> QListView* { return m_ecuList; }

    /**
     * @brief Returns the list view for the Messages section.
     * The View calls this to set the Message Proxy Model.
     */
    [[nodiscard]] auto getMessageList() const -> QListView* { return m_messageList; }

private:
    /**
     * @brief Sets up the whole overview section consisting of 4 areas.
     * 1. File Metadata
     * 2. Row of 4 statistics cards (counts for ECUs, messages, signals, largest message)
     * 3. List overview of all ECUs
     * 4. List overview of all messages
     */
    void setupUi();

    /**
     * @brief Helper to create one of the 4 Statistics cards in the middle section.
     * @param title The gray title text (e.g., "Messages").
     * @param valueLabelPtr Output pointer to the label that will hold the value (mapped later).
     * @param iconName Placeholder for icon resource path.
     */
    auto createStatCard(const QString& title, QLabel*& valueLabelPtr, const QString& iconName) -> QWidget*;

    // Data Mapper for single-value fields
    QDataWidgetMapper* m_mapper;

    // --- Mapped Labels (Targets for m_mapper) ---
    QLabel* m_lblVersion;
    QLabel* m_lblEcuCount;
    QLabel* m_lblMessageCount;
    QLabel* m_lblSignalCount;
    QLabel* m_lblLargestMessageName;

    // --- List Views for the ECUs and Messages Overviews ---
    QListView* m_ecuList;
    QListView* m_messageList;
};

/**
 * @brief The page displaying the ECU hierarchy.
 *
 * VISUALS:
 * - Uses SearchableFilterTree (Search + Filter + Tree).
 * - Standard Qt Expansion (Arrow on the left).
 * - Custom Delegate (EcuTreeDelegate) is used for Card-like rendering of content.
 */
class EcusPage : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Constructs the EcusPage.
     * @param parent The parent widget.
     */
    explicit EcusPage(QWidget* parent = nullptr);
    ~EcusPage() override = default;

    /**
     * @brief Sets the source model for the internal tree view.
     *
     * This is typically called by DbcView to inject the specific
     * TreeFilterProxy instance.
     * @param model The model to be displayed.
     */
    void setModel(QAbstractItemModel* model);

    /**
     * @brief Access to the filter combo box to populate it with options.
     *
     * Allows the caller to add items like "All ECUs", "Sending Nodes only", etc.
     * @return Pointer to the internal QComboBox.
     */
    [[nodiscard]] auto getFilterCombo() const -> QComboBox*;

signals:
    /**
     * @brief Emitted when the user types text into the search bar.
     *
     * The DbcView should connect to this signal to update the filter string
     * of the TreeFilterProxy.
     * @param text The current text in the search field.
     */
    void filterTextChanged(const QString& text);

    /**
     * @brief Emitted when the user selects a different option in the filter combo box.
     *
     * The DbcView should connect to this signal to change the filtering logic
     * of the proxy (e.g. show all vs. show only senders).
     * @param index The index of the selected combo box item.
     */
    void filterTypeChanged(int index);

private:
    /**
     * @brief Initializes the layout, creates the SearchableFilterTree,
     * and installs the EcuTreeDelegate.
     */
    void setupUi();

    /**
     * @brief The internal wrapper widget containing SearchBar, FilterCombo, and TreeView.
     */
    SearchableFilterTree* m_treeWidget;
};
/**
 * @class MessageDetailView
 * @brief The lower half of the Message page showing details(signals) to the selected message in
 * case a message is selected.
 */
class MessageDetailView : public QWidget {
    Q_OBJECT
public:
    explicit MessageDetailView(QWidget* parent = nullptr);

    /**
     * @brief Returns the list view (for the signals).
     * Called by the view to set the Proxy Model.
     */
    [[nodiscard]] auto getSignalList() const -> QListView*;

    /**
     * @brief Sets the title text (Message Name).
     * Called by the Message Page.
     */
    void setMessageTitle(const QString& title);

private:
    /**
     * @brief Assembles the widget.
     */
    void setupUi();

    QLabel* m_lblTitle;      // Name of the selected message
    QListView* m_signalList; // List of signals
};

/**
 * @brief The main page for the Messages Tab (SRS 6.4).
 *
 * INTERACTION LOGIC:
 * - Displays a Master List of all messages (top).
 * - When the user selects a row (click on a table item), the
 *   messageSelectionChanged signal is emitted.
 * - The DbcView catches this and updates the proxies for the Detail View (bottom).
 */
class MessagesPage : public QWidget {
    Q_OBJECT

public:
    explicit MessagesPage(QWidget* parent = nullptr);
    ~MessagesPage() override = default;

    /**
     * @brief Sets the model for the master table (Top).
     * Connects to the selection model to detect row changes.
     */
    void setMasterModel(QAbstractItemModel* model);

    /**
     * @brief Sets the model for the detail view (Bottom).
     * This connects the model to the Signal List.
     */
    void setDetailModel(QAbstractItemModel* model);

    /**
     * @brief Sets the delegate for the signal list (Card rendering).
     */
    void setSignalDelegate(QAbstractItemDelegate* delegate);

    /**
     * @brief Toggles the visibility of the bottom detail pane.
     */
    void showDetailsPane(bool visible);

    /**
     * @brief Access to the filter combo box of the master table.
     */
    [[nodiscard]] auto getMasterFilterCombo() const -> QComboBox*;

signals:
    /**
     * @brief Emitted when the user selects a message in the master table.
     * @param proxyIndex The index in the Proxy Model corresponding to the selected message.
     */
    void messageSelectionChanged(const QModelIndex& proxyIndex);

    /**
     * @brief Emitted when the search text changes.
     */
    void masterFilterTextChanged(const QString& text);

    /**
     * @brief Emitted when the filter dropdown changes.
     */
    void masterFilterTypeChanged(int index);

private slots:
    /**
     * @brief Internal slot connected to the TableView's selection model.
     */
    void onSelectionChanged(const QModelIndex& current, const QModelIndex& previous);

private:
    /**
     * @brief Assembles the messages page.
     */
    void setupUi();

    QSplitter* m_splitter;
    SearchableFilterTable* m_messagesTable; // Master (Top)
    MessageDetailView* m_detailView;      // Detail (Bottom)
};

/**
 * @brief The page displaying a flat list of signals Signals (SRS 6.5).
 *
 * VISUALS:
 * - Top: Search Bar + Filter ComboBox (e.g. "All Units").
 * - Body: A table listing the signals matching search and filter.
 *
 * LOGIC:
 * - Uses a FlatListProxy (TargetType = Signal).
 * - Uses SignalTableDelegate for rendering badges in the Message column.
 */
class SignalsPage : public QWidget {
    Q_OBJECT

public:
    explicit SignalsPage(QWidget* parent = nullptr);
    ~SignalsPage() override = default;

    /**
     * @brief Sets the model for the table view.
     * Called by DbcView to inject the m_allSignalsProxy.
     */
    void setModel(QAbstractItemModel* model);

    /**
     * @brief Access to the filter combo to populate unit filters (e.g. "rpm", "km/h").
     */
    [[nodiscard]] auto getFilterCombo() const -> QComboBox*;

    signals:
        /**
         * @brief Emitted when the user types in the search bar.
         */
        void filterTextChanged(const QString& text);

    /**
     * @brief Emitted when the user changes the Unit filter dropdown.
     */
    void filterTypeChanged(int index);

private:
    void setupUi();


    SearchableFilterTable* m_tableWidget;
};

}