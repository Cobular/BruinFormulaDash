#include "canhandler.h"
#include "external_libs/aemnet_definitions.h"
#include "./utils.h"

using aemnet_utils::msg_t;
using aemnet_utils::msg_00_t;

using namespace Utils;

CanHandler::CanHandler(QObject *parent) :
    QObject(parent),
    m_busStatusTimer(new QTimer(this))
{
    connectCanBus();

    connect(m_busStatusTimer, &QTimer::timeout, this, &CanHandler::busStatus);
}

void CanHandler::connectCanBus()
{
    QString errorString;
    m_canDevice.reset(QCanBus::instance()->createDevice("socketcan", "can0",
                                                        &errorString));
    if (!m_canDevice) {
        setCanStatusMessage(tr("Error creating device '%1', reason: '%2'")
                                 .arg("socketcan").arg(errorString));
        return;
    }

    connect(m_canDevice.get(), &QCanBusDevice::errorOccurred,
            this, &CanHandler::processErrors);
    connect(m_canDevice.get(), &QCanBusDevice::framesReceived,
            this, &CanHandler::processReceivedFrames);
    connect(m_canDevice.get(), &QCanBusDevice::framesWritten,
            this, &CanHandler::processFramesWritten);

    if (!m_canDevice->connectDevice()) {
        setCanStatusMessage(m_canDevice->errorString());

        m_canDevice.reset();
    } else {
        setCanStatusMessage("Connection Appears to have Succeeded!");

        const QVariant bitRate = m_canDevice->configurationParameter(QCanBusDevice::BitRateKey);
        if (bitRate.isValid()) {
//            const bool isCanFd =
//                    m_canDevice->configurationParameter(QCanBusDevice::CanFdKey).toBool();
//            const QVariant dataBitRate =
//                    m_canDevice->configurationParameter(QCanBusDevice::DataBitRateKey);
//            if (isCanFd && dataBitRate.isValid()) {
//                setSocketCanStatus(tr("Plugin: %1, connected to %2 at %3 / %4 kBit/s")
//                `                  .arg(p.pluginName).arg(p.deviceInterfaceName)
//                                  .arg(bitRate.toInt() / 1000).arg(dataBitRate.toInt() / 1000));
//            } else {
//                setSocketCanStatus(tr("Plugin: %1, connected to %2 at %3 kBit/s")
//                                  .arg(p.pluginName).arg(p.deviceInterfaceName)
//                                  .arg(bitRate.toInt() / 1000));
//            }
        }
//        else {
//            setSocketCanStatus(tr("Plugin: %1, connected to %2")
//                    .arg(p.pluginName).arg(p.deviceInterfaceName));
//        }

        if (m_canDevice->hasBusStatus())
            m_busStatusTimer->start(2000);
        else
            setSocketCanStatus(tr("No CAN bus status available."));
    }
}

void CanHandler::busStatus()
{
    if (!m_canDevice || !m_canDevice->hasBusStatus()) {
        setSocketCanStatus(tr("No CAN bus status available."));
        m_busStatusTimer->stop();
        return;
    }

    switch (m_canDevice->busStatus()) {
    case QCanBusDevice::CanBusStatus::Good:
        setSocketCanStatus("CAN bus status: Good.");
        break;
    case QCanBusDevice::CanBusStatus::Warning:
        setSocketCanStatus("CAN bus status: Warning.");
        break;
    case QCanBusDevice::CanBusStatus::Error:
        setSocketCanStatus("CAN bus status: Error.");
        break;
    case QCanBusDevice::CanBusStatus::BusOff:
        setSocketCanStatus("CAN bus status: Bus Off.");
        break;
    default:
        setSocketCanStatus("CAN bus status: Unknown.");
        break;
    }
}

static QString frameFlags(const QCanBusFrame &frame)
{
    QString result = QLatin1String(" --- ");

    if (frame.hasBitrateSwitch())
        result[1] = QLatin1Char('B');
    if (frame.hasErrorStateIndicator())
        result[2] = QLatin1Char('E');
    if (frame.hasLocalEcho())
        result[3] = QLatin1Char('L');

    return result;
}



void CanHandler::processReceivedFrames()
{
    if (!m_canDevice)
        return;

    setNumberFramesWritten(m_numberFramesWritten + 1);

    while (m_canDevice->framesAvailable()) {
        const QCanBusFrame frame = m_canDevice->readFrame();

        QString view;
        if (frame.frameType() == QCanBusFrame::ErrorFrame){
            view = m_canDevice->interpretErrorFrame(frame);
            setCanStatusMessage(view);
            return;
        } else

//        view = frame.toString();

//        const QString time = QString::fromLatin1("%1.%2  ")
//                .arg(frame.timeStamp().seconds(), 10, 10, QLatin1Char(' '))
//                .arg(frame.timeStamp().microSeconds() / 100, 4, 10, QLatin1Char('0'));

//        const QString flags = frameFlags(frame);


        switch (frame.frameId()) {
            case 0x100:
                setTestCanData(framePayloadUint(frame));
                break;
            case 0x1:
                setRpmData(framePayloadUint(frame));
                break;
            case 0x2:
                setCoolantData(framePayloadFloat(frame));
                break;
            case 0x3:
                setVoltageData(framePayloadFloat(frame));
                break;
            case 0x4:
                setAfrData(framePayloadFloat(frame));
                break;
            case 0x5:
                setBiasData(framePayloadFloat(frame));
                break;
            case AEMNET_MSG_ID(0x00):
                msg_00_t* msg_00 = (msg_00_t *)framePayloadMessage(frame);
                qDebug() << "Coolant Temp: " << msg_00->coolant_temp << " Intake Temp: " << msg_00->intake_temp;
                break;
        }
    }
}

void CanHandler::processFramesWritten(qint64 count)
{
    setNumberFramesWritten(m_numberFramesWritten + count);
}

void CanHandler::processErrors(QCanBusDevice::CanBusError error)
{
    switch (error) {
    case QCanBusDevice::ReadError:
    case QCanBusDevice::WriteError:
    case QCanBusDevice::ConnectionError:
    case QCanBusDevice::ConfigurationError:
    case QCanBusDevice::UnknownError:
        setCanStatusMessage(m_canDevice->errorString());
        break;
    default:
        break;
    }
}
