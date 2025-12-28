#ifndef SENDINGMODEL_H
#define SENDINGMODEL_H
#include <cstdint>
#include <vector>
#include <QAbstractTableModel>



struct SendingMessageConfig {
    bool isActive;
    uint32_t canId;
    std::vector<uint8_t> payload;
    int cycleTime;

};
#endif