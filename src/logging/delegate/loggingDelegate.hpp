#ifndef LOGGINGDELEGATE_H
#define LOGGINGDELEGATE_H
#include <QStyledItemDelegate>

namespace Logging {
class LoggingDelegate : public QStyledItemDelegate
{
    Q_OBJECT

   public:
    explicit LoggingDelegate(QObject *parent = nullptr);

    // We override paint to customize the look of the log entries
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    // We can also suggest a better size for specific columns
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
}  // namespace Logging
#endif  // LOGGINGDELEGATE_H
