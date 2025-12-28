#pragma once
#include <QWidget>
#include <string>

#include "i_lifecycle.hpp"

namespace Core {

/**
 * @brief Interface for a UI component that represents a single tab in the application.
 *
 * This class combines the application lifecycle (Start/Stop) with the UI requirements
 * needed to render within a Qt environment.
 */
class ITabComponent : public ILifecycle
{
   public:
    /**
     * @brief Constructs the tab component.
     * @param broker Reference to the event broker for communication.
     * @param title The display name of the tab in the UI.
     */
    ITabComponent(IEventBroker& broker, std::string title)
        : ILifecycle(broker), m_title(std::move(title))
    {
    }

    /**
     * @brief Virtual destructor.
     */
    virtual ~ITabComponent() override = default;

    /**
     * @brief Returns the Qt widget associated with this tab.
     * * @details The root window or tab manager will call this to retrieve the
     * visual representation of the component for embedding into the GUI.
     * @return QWidget* Pointer to the tab's root widget.
     */
    virtual QWidget* getView() = 0;

    /**
     * @brief Returns the display title of the tab.
     * @return const std::string& The title string.
     */
    const std::string& getTitle() const
    {
        return m_title;
    }

   protected:
    /**
     * @brief Display title used by the UI container.
     */
    std::string m_title;
};

}  // namespace Core