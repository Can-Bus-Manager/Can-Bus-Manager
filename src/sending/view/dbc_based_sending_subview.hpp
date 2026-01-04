#pragma once

#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QWidget>
#include <string>
#include <vector>

#include "common/widgets/dbc_message_card.hpp"

namespace Sending {

/**
 * @class DbcSendingSubView
 * @brief The primary container for the DBC-based workflow.
 * * @section Hierarchy
 * 1. **Configuration:** Top card for interface selection.
 * 2. **Message List:** A scrollable area where the Delegate injects @ref DbcMessageCardWidget.
 * 3. **Footer:** A floating or fixed area for the "Send Message" action.
 */
class DbcSendingSubView final : public QWidget
{
    Q_OBJECT
   public:
    explicit DbcSendingSubView(QWidget* parent = nullptr);
    ~DbcSendingSubView() override = default;

    /**
     * @name Dynamic Content API
     * The Delegate uses these to populate the scroll area based on the loaded DBC.
     */
    void addMessageCard(Common::Widgets::DbcMessageCard* card);
    void clearMessages();

    /**
     * @name Control Accessors
     */
    [[nodiscard]] auto interfaceSelector() const -> QComboBox*
    {
        return m_interfaceCombo;
    }
    [[nodiscard]] auto sendButton() const -> QPushButton*
    {
        return m_sendButton;
    }

    void setAvailableInterfaces(const std::vector<std::string>& interfaces);

   private:
    void setupUi();

    // --- Section 1: Config Header ---
    QGroupBox* m_configGroup;
    QComboBox* m_interfaceCombo;

    // --- Section 2: Scrollable Message List ---
    QLabel* m_listHeader;  ///< "Messages" label
    QScrollArea* m_scrollArea;
    QWidget* m_scrollContent;    ///< The widget inside the scroll area
    QVBoxLayout* m_cardsLayout;  ///< Layout holding the MessageCards

    // --- Section 3: Floating Footer ---
    QPushButton* m_sendButton;  ///< "Send Message" button (bottom right)
};

}  // namespace Sending