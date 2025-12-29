#ifndef CANBUSMANAGER_SIGNAL_TREE_DELEGATE_HPP
#define CANBUSMANAGER_SIGNAL_TREE_DELEGATE_HPP
#include <QStyledItemDelegate>

#endif  // CANBUSMANAGER_SIGNAL_TREE_DELEGATE_HPP

namespace Monitoring {
class SignalTreeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    public:
    explicit SignalTreeDelegate(QObject* parent = nullptr);
    ~SignalTreeDelegate() override = default;

    QString displayText(const QVariant& value,
                const QLocale& locale) const override;
};
}