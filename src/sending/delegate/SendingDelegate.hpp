#ifndef SENDING_DELEGATE_HPP
#define SENDING_DELEGATE_HPP
#include <QStyledItemDelegate>
#include <QWidget>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QStyleOptionViewItem>
#include "core/interface/i_event_broker.hpp"
using Core::IEventBroker;

namespace Sending {
class SendingDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit SendingDelegate(IEventBroker* eventBroker, QObject* parent = nullptr);
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                     const QModelIndex &index) const override;
};
}
#endif // SENDING_DELEGATE_HPP
