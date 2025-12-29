#ifndef CANBUSMANAGER_DECODED_SIGNAL_HPP
#define CANBUSMANAGER_DECODED_SIGNAL_HPP
#include <qvariant.h>

#endif  // CANBUSMANAGER_DECODED_SIGNAL_HPP

namespace Core {
class DecodedSignal
{
public:
    DecodedSignal(QString name, QVariant value, QString unit, QVariant rawVal);
    QString getName();
    QVariant getValue();
    QString getUnit();
    QVariant getRaw();

private:
    QString name;
    QVariant value;
    QString unit;
    QVariant rawVal; //Encoded part-signal
};
}