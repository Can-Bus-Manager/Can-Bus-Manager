#pragma once

#include <QStackedWidget>
#include <QTabBar>
#include <QVBoxLayout>
#include <QWidget>

#include "app_root/delegate/app_root_delegate.hpp"
#include "app_root/model/app_root_model.hpp"
#include "core/interface/i_tab_component.hpp"

namespace AppRoot {

/**
 * @class AppRootView
 * @brief The main UI Shell (Compositor).
 * @details
 * Manages a QTabBar at the top and a QStackedWidget for the main content.
 * It uses a standard QVBoxLayout to stack the navigation and content areas.
 */
class AppRootView : public QWidget
{
    Q_OBJECT
   public:
    explicit AppRootView(QWidget* parent = nullptr);
    ~AppRootView() override = default;

    /**
     * @brief Injects the model and sets up synchronization logic.
     * @param model Pointer to the data model.
     */
    void setModel(AppRootModel* model);

    /**
     * @brief Sets the delegate for custom tab bar rendering.
     * @param delegate Pointer to the tab delegate.
     */
    void setDelegate(AppRootDelegate* delegate);

   private slots:
    /**
     * @brief Reacts to model changes to add tabs in the UI.
     */
    void onRowsInserted(const QModelIndex& parent, int first, int last);

    /**
     * @brief Reacts to model changes to remove tabs in the UI.
     */
    void onRowsAboutToBeRemoved(const QModelIndex& parent, int first, int last);

    /**
     * @brief Handles metadata changes (title/icon) from the model.
     */
    void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight,
                       const QList<int>& roles);

    /**
     * @brief Handles tab switching to keep the stack in sync.
     */
    void handleTabChanged(int index);

   private:
    /**
     * @brief The tab bar populated by the options provided in the m_tabs.
     */
    QTabBar* m_tabBar;

    /**
     * @brief The different Widgets of the tabs with one selected.
     */
    QStackedWidget* m_contentStack;

    /**
     * @brief Layout to order The m_tabBar and m_contentStack.
     */
    QVBoxLayout* m_mainLayout;

    /**
     * @brief Pointer to the injected model.
     */
    AppRootModel* m_model = nullptr;
};

}  // namespace AppRoot