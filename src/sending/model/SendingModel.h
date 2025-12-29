#ifndef SENDINGMODEL_H
#define SENDINGMODEL_H
#include <cstdint>
#include <vector>
#include <QAbstractTableModel> // oder QAbstractItemModel
#include "IEventBroker.h"


//move to core?
struct MessageConfig {
    uint32_t canId;           
    std::vector<uint8_t> data; 
    int cycleTimeMs;
    bool isCyclicActive;
    bool isDbcBased;
    QTimer* timer = nullptr;
};

std::vector<MessageConfig> m_messages;

#endif