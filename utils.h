#ifndef UTILS_H
#define UTILS_H

#include <qbytearray.h>
#include <QString>
#include <QCanBus>
#include "external_libs/aemnet_definitions.h"

using aemnet_utils::msg_t;

namespace Utils {
    union floatData {
        float f;
        unsigned char fBuff[sizeof(float)];
    };

    union int32Data {
      qint32 i;
      unsigned char iBuff[sizeof(qint32)];
    };

    union int16Data {
      qint16 i;
      unsigned char iBuff[sizeof(qint16)];
    };


    float makeFloat(QByteArray arr);
    qint32 makeInt32(QByteArray arr);
    qint16 makeInt16(QByteArray arr);

    QString framePayloadString(const QCanBusFrame &frame);
    qlonglong framePayloadUint(const QCanBusFrame &frame);
    float framePayloadFloat(const QCanBusFrame &frame);
    msg_t* framePayloadMessage(const QCanBusFrame &frame);
}


#endif // UTILS_H
