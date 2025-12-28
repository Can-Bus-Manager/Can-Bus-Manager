#pragma once

#include <QAbstractItemDelegate>
#include <QAbstractItemModel>
#include <QStackedWidget>
#include <QTabBar>
#include <QWidget>
#include <vector>

#include "core/interface/i_tab_component.hpp"

namespace AppRoot {

/**
 * @class AppRootView
 * @brief The main UI Shell (Compositor).
 * @details
 * Manages a QTabBar at the top and a QStackedWidget for the main content.
 * It is a pure container that receives its data and rendering logic via DI.
 */
class AppRootView : public QWidget
{
    Q_OBJECT
   public:
    explicit AppRootView(QWidget* parent = nullptr);
    ~AppRootView() override;

    /**
     * @brief Injects the Model and Delegate into the view.
     * @details The Model provides tab info, while the Delegate paints the shell.
     */
    void setMvd(QAbstractItemModel* model, QAbstractItemDelegate* delegate);

    /**
     * @brief Populates the navigation and content areas.
     * @param tabs Vector of components to be rendered as tab pages.
     */
    void setTabs(const std::vector<Core::ITabComponent*>& tabs);

   private:
    QTabBar* m_tabBar;
    QStackedWidget* m_contentStack;
};

}  // namespace AppRoot