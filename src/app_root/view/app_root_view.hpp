#pragma once

#include <QStackedWidget>
#include <QTabBar>
#include <QWidget>
#include <QVBoxLayout>
#include <vector>

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
     * @brief Populates the navigation and content areas.
     * @param tabs Vector of components to be rendered as tab pages.
     */
    void setTabs(const std::vector<Core::ITabComponent*>& tabs);

private slots:
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
     * @brief Internal tracking of the components to map indices back to the interface.
     */
    QList<Core::ITabComponent*> m_tabs;
};

}  // namespace AppRoot