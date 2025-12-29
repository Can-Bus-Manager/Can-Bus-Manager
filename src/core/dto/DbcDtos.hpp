//
// Created by Adrian Rupp on 29.12.25.
//

#pragma once
#include <QString>
#include <vector>

namespace Core {

/**
 * @brief Data container for Signal.
 */
struct DbcSignal {
    QString name;
    int startBit;
    int length;
    double factor;
    double offset;
    QString unit;
    double min;
    double max;
};

/**
 * @brief Data container for Message.
 */
struct DbcMessage {
    unsigned int id;
    QString name;
    int dlc;
    QString senderEcu;
    std::vector<DbcSignal> signalVector;
};

/**
 * @brief Data container for Ecu
 */
struct DbcEcu {
    QString name;
    std::vector<unsigned int> txMessageIds;
};

/**
 * @brief Main DTO combining everything.
 */
struct DbcConfig {
    std::vector<DbcEcu> ecus;
    std::vector<DbcMessage> messages;
};

} // namespace Core
