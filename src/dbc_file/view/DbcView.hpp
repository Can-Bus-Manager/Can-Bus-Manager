//
// Created by Adrian Rupp on 28.12.25.
//
#pragma once

#include <QDataWidgetMapper>
#include <QListView>
#include <QStackedWidget>
#include <QWidget>
#include <memory>

#include "SubViews.hpp"

namespace Dbc {

class DbcView : public QWidget {
    Q_OBJECT

public:
    explicit DbcView(QWidget* parent = nullptr);
    ~DbcView() override;

    /**
     * @brief Injects the raw source model.
     * The View creates its own Proxies wrapping this model.
     */
    void setSourceModel(QAbstractItemModel* model);

    /**
     * @brief Sets the delegate for all internal views.
     */
    void setItemDelegate(QAbstractItemDelegate* delegate);

    /**
     * @brief Unlocks navigation after successful load.
     */
    void setNavigationEnabled(bool enabled);

signals:
    /** @brief Notify Dbc Component to request file loading */
    void fileLoadRequested(const QString& filePath);

private slots:
    /** @brief Handle sidebar selection change (show different page) */
    void onSidebarSelectionChanged(int index);


    /** @brief Handle change in ECU search bar (set proxy filter) */
    void onEcuSearchChanged(const QString& text);

    /** @brief Handle change in message search bar (set proxy filter) */
    void onMessageSearchChanged(const QString& text);

    /** @brief Handle change in signal search bar (set proxy filter) */
    void onSignalSearchChanged(const QString& text);

    // Master-Detail: Message ausgewählt -> Signal-Proxy filtern & Detail View zeigen

    /** @brief Handle message table selection change (show signals for selected message) */
    void onMessageTableSelectionChanged(const QModelIndex& index);

private:
    void setupUi();
    void createSubViews();
    void setupConnections();

    // UI Structure
    QListView* m_sidebarList;
    QStackedWidget* m_contentStack;

    // Pages
    DbcLoadPage* m_loadPage;
    QWidget* m_overviewPage;
    DbcSearchTreeView* m_ecuTreeView;
    DbcMessagesPage* m_messagesPage;
    DbcSearchTableView* m_signalsPage;

    QDataWidgetMapper* m_overviewMapper;

    // --- Proxies ---
    std::unique_ptr<DbcTypeFilterProxy> m_messagesProxy;
    std::unique_ptr<DbcTypeFilterProxy> m_messageDetailsProxy;
    std::unique_ptr<DbcTypeFilterProxy> m_SignalsProxy;
};

} // namespace CanBusManager::Dbc
