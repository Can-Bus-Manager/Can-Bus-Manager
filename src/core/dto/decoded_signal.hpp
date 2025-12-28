#ifndef CANBUSMANAGER_DECODED_SIGNAL_HPP
#define CANBUSMANAGER_DECODED_SIGNAL_HPP

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
#endif  // CANBUSMANAGER_DECODED_SIGNAL_HPP