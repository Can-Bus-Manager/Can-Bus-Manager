#include "LoggingDelegate.h"
#include <QPainter>
#include <QFontDatabase>


LoggingDelegate::LoggingDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {
}

void LoggingDelegate::paint(QPainter *painter, 
                           const QStyleOptionViewItem &option, 
                           const QModelIndex &index) const {
    
    /*
     * This method handles the custom rendering of each cell in the logging table.
     * * 1. Visual Styling:
     * It can modify the font to ensure readability.
     * * 2. Conditional Formatting:
     * It retrieves the "Direction" data (TX or RX) from the model. Based on this, 
     * it can change the text color to help users distinguish between outgoing and incoming traffic at a glance.
     * * 3. Selection Handling:
     * It ensures that when a row is selected, the background and text colors 
     * conform to the system's highlight palette.
     * * 4. Painting:
     * Finally, it uses the QPainter to draw the text.
     */
}

QSize LoggingDelegate::sizeHint(const QStyleOptionViewItem &option, 
                               const QModelIndex &index) const {
    /*
     * This method provides the view with the ideal size for a specific cell.
     * * 1. Padding and Spacing:
     * It calculates the default size required for the text content and adds 
     * custom padding (vertical or horizontal) to prevent the log entries 
     * from looking too cramped, especially during high-speed data bursts.
     * * 2. Content Awareness:
     * It can suggest different heights or widths based on the column index 
     * (e.g., ensuring the Timestamp column is wide enough for millisecond precision).
     */
}