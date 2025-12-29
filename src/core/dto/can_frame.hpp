#ifndef CANBUSMANAGER_CAN_FRAME_HPP
#define CANBUSMANAGER_CAN_FRAME_HPP

#include <QDateTime>
#include "decoded_signal.hpp"

#endif  // CANBUSMANAGER_CAN_FRAME_HPP
namespace Core {
class CanFrame
{
public:
    CanFrame(uint32_t messageId, QByteArray payload);
    QDateTime getTimestamp();
    uint32_t getMessageId();
    QByteArray getPayload();
    DecodedSignal getSignal(QString signalName);
    QList<QString> getSignals();

private:
    QDateTime timestamp;
    uint32_t messageId;
    QByteArray payload;
    QVector<DecodedSignal> decodedSignals;
};
}