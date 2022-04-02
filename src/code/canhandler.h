#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <qqml.h>
#include <QtSerialBus/QCanBus>
#include <QDebug>
#include <QTimer>

class CanHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qint64 numberFramesWritten READ numberFramesWritten WRITE setNumberFramesWritten NOTIFY numberFramesWrittenChanged)
    Q_PROPERTY(QString canStatusMessage READ canStatusMessage WRITE setCanStatusMessage NOTIFY canStatusMessageChanged)
    Q_PROPERTY(QString socketCanStatus READ socketCanStatus WRITE setSocketCanStatus NOTIFY socketCanStatusChanged)
    Q_PROPERTY(qint64 testCanData READ testCanData WRITE setTestCanData NOTIFY testCanDataChanged)


    Q_PROPERTY(qint64 rpmData READ rpmData WRITE setRpmData NOTIFY rpmDataChanged)

    QML_ELEMENT

public:
    explicit CanHandler(QObject *parent = nullptr);

    // 0 is success, > 0 is error
    void connectCanBus();
    void processErrors(QCanBusDevice::CanBusError);
    void processReceivedFrames();
    void processFramesWritten(qint64 count);
    void busStatus();

    void setNumberFramesWritten(const qint64 &a);
    qint64 numberFramesWritten() const;

    void setCanStatusMessage(const QString &a);
    QString canStatusMessage() const;

    void setTestCanData(const qint64 &a);
    qint64 testCanData() const;

    void setRpmData(const qint64 &a);
    qint64 rpmData() const;

    void setSocketCanStatus(const QString &a);
    QString socketCanStatus() const;

signals:
    void numberFramesWrittenChanged();
    void canStatusMessageChanged();
    void socketCanStatusChanged();
    void testCanDataChanged();
    void rpmDataChanged();

    void canConnectionFailed(QString err_str);
    void canConnectionSuccess(QString conn_str);

private:
    qint64 m_numberFramesWritten = 0;
    QString m_canStatusMessage = "No Status Yet..";
    QString m_socketCanStatus = "No Status Yet..";
    qint64 m_canTestData = -1;
    qint64 m_rmpData = -1;
    std::unique_ptr<QCanBusDevice> m_canDevice;
    QTimer *m_busStatusTimer = nullptr;
};

#endif // BACKEND_H
