#ifndef CANBUSMANAGER_SIGNAL_TREE_DELEGATE_HPP
#define CANBUSMANAGER_SIGNAL_TREE_DELEGATE_HPP
#include <QStyledItemDelegate>

#endif  // CANBUSMANAGER_SIGNAL_TREE_DELEGATE_HPP

/**
 * @namespace Monitoring
 * @brief Contains delegate and UI components for CAN signal monitoring.
 */
namespace Monitoring {

/**
 * @class SignalTreeDelegate
 * @brief Delegate responsible for custom rendering of signal tree items.
 *
 * SignalTreeDelegate customizes how CAN frames and signals are displayed
 * within the SignalTreeView. It operates purely on presentation logic and
 * does not modify the underlying model data.
 *
 * Typical responsibilities:
 * - Format display text for frames and signals
 * - Control localization-sensitive string rendering
 * - Ensure consistent visual representation across the tree view
 */
class SignalTreeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
   public:
    /**
     * @brief Constructs the signal tree delegate.
     *
     * @param parent Optional Qt parent object.
     */
    explicit SignalTreeDelegate(QObject* parent = nullptr);

    /**
     * @brief Default destructor.
     */
    ~SignalTreeDelegate() override = default;

    /**
     * @brief Returns the formatted display text for a model value.
     *
     * This method is invoked by the view to obtain the user-visible string
     * representation of model data, allowing domain-specific formatting
     * without altering the model itself.
     *
     * @param value  The data value provided by the model.
     * @param locale The locale used for formatting.
     * @return Localized, formatted display string.
     */
    [[nodiscard]] auto displayText(const QVariant& value,
        const QLocale& locale) const
        -> QString override;
};
}  // namespace Monitoring