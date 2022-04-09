#ifndef DEBUG_CONSOLE_H
#define DEBUG_CONSOLE_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#define DEBUG_CONSOLE_LINE_COUNT 10

class DebugConsole : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString consoleText READ getConsoleText NOTIFY consoleTextChanged)
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)

public:
    explicit DebugConsole(QQuickItem *parent = nullptr);
    void writeLine(QString line);
    virtual void paint(QPainter *painter);
    QString getConsoleText() const {
        return consoleText;
    }

    QColor getColor() const {
        return color;
    }
    void setColor(const QColor &color) {
        if (this->color != color) {
            this->color = color;
            emit colorChanged();
        }
    }
signals:
    void consoleTextChanged();
    void colorChanged();
private:
    QString consoleText;
    QColor color;
    QString lines[DEBUG_CONSOLE_LINE_COUNT];
    qint32 toplineindex;
    qint32 numlines;
};

#endif // DEBUG_CONSOLE_H
