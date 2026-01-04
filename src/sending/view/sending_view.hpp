#pragma once

#include <QComboBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

#include "dbc_based_sending_subview.hpp"
#include "raw_sending_subview.hpp"

namespace Sending {

/**
 * @brief The main container view for the Sending tab.
 * Manages the sidebar navigation and the configuration header.
 */
class SendingView final : public QWidget
{
    Q_OBJECT

   public:
    explicit SendingView(QWidget* parent = nullptr);
    ~SendingView() override = default;

    // Accessors for the Delegate to wire up signals/slots
    RawSendingSubView* rawSubView() const
    {
        return m_rawView;
    }
    DbcSendingSubView* dbcSubView() const
    {
        return m_dbcView;
    }

    // UI Interaction API
    void setAvailableDevices(const std::vector<std::string>& devices);
    void setAvailableSpeeds(const std::vector<uint32_t>& speeds);

   signals:
    /** @brief Emitted when the sidebar "Raw" or "DBC" buttons are clicked */
    void modeChanged(bool isDbcMode);

    /**
     * @brief Emitted when the "Send Message" footer button is clicked.
     */
    void sendClicked();

    /** @brief Emitted when the device dropdown changes */
    void deviceSelectionChanged(const std::string& deviceName);

   public slots:
    /** @brief Switches the visible sub-view (0 for Raw, 1 for DBC) */
    void displayMode(int index);

   private:
    void setupUi();

    // Sidebar buttons
    QPushButton* m_btnRawMode;
    QPushButton* m_btnDbcMode;

    QStackedWidget* m_contentStack;
    RawSendingSubView* m_rawView;
    DbcSendingSubView* m_dbcView;
};

}  // namespace Sending