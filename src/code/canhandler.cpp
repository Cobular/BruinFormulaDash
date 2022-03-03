#include "canhandler.h"

CanHandler::CanHandler(QObject *parent) :
    QObject(parent)
{
    connectCanBus();

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
            const bool isCanFd =
                    m_canDevice->configurationParameter(QCanBusDevice::CanFdKey).toBool();
            const QVariant dataBitRate =
                    m_canDevice->configurationParameter(QCanBusDevice::DataBitRateKey);
//            if (isCanFd && dataBitRate.isValid()) {
//                m_status->setText(tr("Plugin: %1, connected to %2 at %3 / %4 kBit/s")
//                                  .arg(p.pluginName).arg(p.deviceInterfaceName)
//                                  .arg(bitRate.toInt() / 1000).arg(dataBitRate.toInt() / 1000));
//            } else {
//                m_status->setText(tr("Plugin: %1, connected to %2 at %3 kBit/s")
//                                  .arg(p.pluginName).arg(p.deviceInterfaceName)
//                                  .arg(bitRate.toInt() / 1000));
//            }
        } else {
//            m_status->setText(tr("Plugin: %1, connected to %2")
//                    .arg(p.pluginName).arg(p.deviceInterfaceName));
        }

//        if (m_canDevice->hasBusStatus())
//            m_busStatusTimer->start(2000);
//        else
//            m_ui->busStatus->setText(tr("No CAN bus status available."));
    }
}

//void CanHandler::busStatus()
//{
//    if (!m_canDevice || !m_canDevice->hasBusStatus()) {
//        m_ui->busStatus->setText(tr("No CAN bus status available."));
//        m_busStatusTimer->stop();
//        return;
//    }

//    switch (m_canDevice->busStatus()) {
//    case QCanBusDevice::CanBusStatus::Good:
//        m_ui->busStatus->setText("CAN bus status: Good.");
//        break;
//    case QCanBusDevice::CanBusStatus::Warning:
//        m_ui->busStatus->setText("CAN bus status: Warning.");
//        break;
//    case QCanBusDevice::CanBusStatus::Error:
//        m_ui->busStatus->setText("CAN bus status: Error.");
//        break;
//    case QCanBusDevice::CanBusStatus::BusOff:
//        m_ui->busStatus->setText("CAN bus status: Bus Off.");
//        break;
//    default:
//        m_ui->busStatus->setText("CAN bus status: Unknown.");
//        break;
//    }
//}

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
        }

        view = frame.toString();

        const QString time = QString::fromLatin1("%1.%2  ")
                .arg(frame.timeStamp().seconds(), 10, 10, QLatin1Char(' '))
                .arg(frame.timeStamp().microSeconds() / 100, 4, 10, QLatin1Char('0'));

        const QString flags = frameFlags(frame);

        setTestCanData(view.toInt());
//        m_ui->receivedMessagesEdit->append(time + flags + view);
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
