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
    Q_PROPERTY(qint64 coolantData READ coolantData WRITE setCoolantData NOTIFY coolantDataChanged)
    Q_PROPERTY(qint64 afrData READ afrData WRITE setAfrData NOTIFY afrDataChanged)
    Q_PROPERTY(qint64 biasData READ biasData WRITE setBiasData NOTIFY biasDataChanged)
    Q_PROPERTY(qint64 voltageData READ voltageData WRITE setVoltageData NOTIFY voltageDataChanged)

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
    void setCoolantData(const qint64 &a);
    qint64 coolantData() const;
    void setAfrData(const qint64 &a);
    qint64 afrData() const;
    void setBiasData(const qint64 &a);
    qint64 biasData() const;
    void setVoltageData(const qint64 &a);
    qint64 voltageData() const;

    void setSocketCanStatus(const QString &a);
    QString socketCanStatus() const;

signals:
    void numberFramesWrittenChanged();
    void canStatusMessageChanged();
    void socketCanStatusChanged();
    void testCanDataChanged();

    void rpmDataChanged();
    void coolantDataChanged();
    void afrDataChanged();
    void biasDataChanged();
    void voltageDataChanged();

    void canConnectionFailed(QString err_str);
    void canConnectionSuccess(QString conn_str);

private:
    qint64 m_numberFramesWritten = 0;
    QString m_canStatusMessage = "No Status Yet..";
    QString m_socketCanStatus = "No Status Yet..";
    qint64 m_canTestData = -1;

    qint64 m_rmpData = -1;
    qint64 m_coolantData = -1;
    qint64 m_afrData = -1;
    qint64 m_biasData = -1;
    qint64 m_voltageData = -1;

    std::unique_ptr<QCanBusDevice> m_canDevice;
    QTimer *m_busStatusTimer = nullptr;
};

#endif // BACKEND_H
