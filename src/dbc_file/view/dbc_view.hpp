//
// Created by Adrian Rupp on 28.12.25.
//
#pragma once

#include <qboxlayout.h>

#include <QDataWidgetMapper>
#include <QListView>
#include <QStackedWidget>
#include <QWidget>

#include "subviews.hpp"
#include "proxies.hpp"

namespace Dbc {

/**
 * @brief The main container for the DBC Tab (Composite View).
 *
 * RESPONSIBILITIES:
 * 1. Layout: Manages the Sidebar and the Page Stack (Load, Overview, ECUs, Messages, Signals).
 * 2. Data Wiring: Creates the specific Proxy Models needed for each page and connects them.
 * 3. Interaction Logic: connects Search Bars and Filter Combos from the pages to the Proxies.
 */
class DbcView : public QWidget {
    Q_OBJECT

public:
    explicit DbcView(QWidget* parent = nullptr);
    ~DbcView() override;

    /**
     * @brief Initializes the view with the source data.
     *
     * This method is called by the Component after the DBC file is parsed.
     * It instantiates all Proxy Models, injects the source model into them,
     * and sets the proxies on the respective Pages.
     */
    void setSourceModel(QAbstractItemModel* model);

    /**
     * @brief Unlocks navigation (Sidebar) after a successful file load.
     *
     * Initially, only the LoadPage is accessible. Once data is loaded,
     * the Component calls this to enable switching to Overview/ECUs/etc.
     */
    void setNavigationEnabled(bool enabled);

signals:
    /**
     * @brief Forwarded signal from LoadPage.
     * Tells the DbcComponent that the user has selected a file to parse.
     */
    void fileLoadRequested(const QString& filePath);

private slots:
    /**
     * @brief Handles sidebar navigation to switch the active page in the stack.
     */
    void onSidebarSelectionChanged(const QModelIndex& index);

    // --- ECU PAGE INTERACTION ---
    void onEcuFilterTextChanged(const QString& text);
    void onEcuFilterTypeChanged(int index);

    // --- MESSAGES PAGE INTERACTION ---
    void onMessageFilterTextChanged(const QString& text);
    void onMessageFilterTypeChanged(int index);

    /**
     * @brief Master-Detail Logic for Messages Page.
     *
     * Called when a row is selected in the Message Master Table.
     * 1. Maps the proxy index to the source index.
     * 2. Updates the m_messageDetailProxy to show children of this message.
     * 3. Updates the Detail View title.
     */
    void onMessageSelected(const QModelIndex& proxyIndex);

    // --- SIGNALS PAGE INTERACTION ---

    /**
     * @brief Updates the m_allSignalsProxy search filter.
     */
    void onSignalFilterTextChanged(const QString& text);
    /**
     * @brief Updates the m_allSignalsProxy category filter (e.g. Unit).
     */
    void onSignalFilterTypeChanged(int index);

private:
    void setupUi();
    void createSubViews();
    void setupConnections();

    // --- UI Structure ---
    QListView* m_sidebarList;
    QStackedWidget* m_contentStack;

    // --- Pages (Raw pointers because Qt manages their memory via parent) ---
    LoadPage* m_loadPage;
    OverviewPage* m_overviewPage;
    EcusPage* m_ecuPage;
    MessagesPage* m_messagesPage;
    SignalsPage* m_signalsPage;

    // --- Data Proxies (Owned by the View) ---

    /**
     * @brief Hierarchy filter for the ECU Page.
     * Maintains tree structure (Root->ECU->Message->Signal).
     */
    std::unique_ptr<TreeFilterProxy> m_ecuTreeProxy;

    /**
     * @brief Flat list of ECUs for the Overview Page (Tiles).
     * Flattens the tree to just show ECU nodes.
     */
    std::unique_ptr<FlatListProxy> m_ecuOverviewProxy;

    /**
     * @brief Flat list of Messages.
     * SHARED by:
     * 1. Overview Page (Messages Tile List)
     * 2. Messages Page (Master Table)
     */
    std::unique_ptr<FlatListProxy> m_messagesProxy;

    /**
     * @brief Detail filter for Messages Page.
     * Shows only signals of the currently selected message.
     */
    std::unique_ptr<SingleMessageProxy> m_messageDetailProxy;

    /**
     * @brief Flat list of the Signals in the system.
     * Used for the Signals Page.
     */
    std::unique_ptr<FlatListProxy> m_signalsProxy;
};

} // namespace CanBusManager::Dbc
