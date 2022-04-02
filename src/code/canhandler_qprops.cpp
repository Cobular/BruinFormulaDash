#include "canhandler.h"


void CanHandler::setNumberFramesWritten(const qint64 &a) {
    if (a != m_numberFramesWritten) {
        m_numberFramesWritten = a;
        emit numberFramesWrittenChanged();
    }
}
qint64 CanHandler::numberFramesWritten() const {
    return m_numberFramesWritten;
}

void CanHandler::setCanStatusMessage(const QString &a) {
    if (a != m_canStatusMessage) {
        m_canStatusMessage = a;
        emit numberFramesWrittenChanged();
    }
}
QString CanHandler::canStatusMessage() const {
    return m_canStatusMessage;
}

void CanHandler::setTestCanData(const qint64 &a) {
    QString test = QStringLiteral("%1").arg(a);
    qDebug() << qPrintable(test);
    if (a != m_canTestData) {
        m_canTestData = a;
        emit testCanDataChanged();
    }
}
qint64 CanHandler::testCanData() const {
    return m_canTestData;
}

void CanHandler::setRpmData(const qint64 &a) {
    if (a != m_rmpData) {
        m_rmpData = a;
        emit rpmDataChanged();
    }
}
qint64 CanHandler::rpmData() const {
    return m_rmpData;
}

void CanHandler::setSocketCanStatus(const QString &a) {
    if (a != m_socketCanStatus) {
        m_socketCanStatus = a;
        emit socketCanStatusChanged();
    }
}
QString CanHandler::socketCanStatus() const {
    return m_socketCanStatus;
}
