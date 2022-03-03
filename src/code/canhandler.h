#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <qqml.h>
#include <QtSerialBus/QCanBus>
#include <QDebug>

class CanHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint64 numberFramesWritten READ numberFramesWritten WRITE setNumberFramesWritten NOTIFY numberFramesWrittenChanged)
    Q_PROPERTY(QString canStatusMessage READ canStatusMessage WRITE setCanStatusMessage NOTIFY canStatusMessageChanged)
    Q_PROPERTY(QString socketCanStatus READ socketCanStatus WRITE setSocketCanStatus NOTIFY socketCanStatusChanged)
    Q_PROPERTY(qint64 testCanData READ testCanData WRITE setTestCanData NOTIFY testCanDataChanged)
    QML_ELEMENT

public:
    explicit CanHandler(QObject *parent = nullptr);

    // 0 is success, > 0 is error
    void connectCanBus();
    void processErrors(QCanBusDevice::CanBusError);
    void processReceivedFrames();
    void processFramesWritten(qint64 count);
    void busStatus();

    void setNumberFramesWritten(const qint64 &a) {
        if (a != m_numberFramesWritten) {
            m_numberFramesWritten = a;
            emit numberFramesWrittenChanged();
        }
    }
    qint64 numberFramesWritten() const {
        return m_numberFramesWritten;
    }

    void setCanStatusMessage(const QString &a) {
        if (a != m_canStatusMessage) {
            m_canStatusMessage = a;
            emit numberFramesWrittenChanged();
        }
    }
    QString canStatusMessage() const {
        return m_canStatusMessage;
    }

    void setTestCanData(const qint64 &a) {
        QString test = QStringLiteral("%1").arg(a);
        qDebug(qPrintable(test));
        if (a != m_canTestData) {
            m_canTestData = a;
            emit testCanDataChanged();
        }
    }
    qint64 testCanData() const {
        return m_canTestData;
    }

signals:
    void numberFramesWrittenChanged();
    void canStatusMessageChanged();
    void testCanDataChanged();

    void canConnectionFailed(QString err_str);
    void canConnectionSuccess(QString conn_str);

private:
    qint64 m_numberFramesWritten = 0;
    QString m_canStatusMessage = "No Status Yet..";
    qint64 m_canTestData = -1;
    std::unique_ptr<QCanBusDevice> m_canDevice;
};

#endif // BACKEND_H
