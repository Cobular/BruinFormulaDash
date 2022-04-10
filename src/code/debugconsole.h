#ifndef DEBUG_CONSOLE_H
#define DEBUG_CONSOLE_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>

class DebugConsole : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qint32 fontSize READ getFontSize WRITE setFontSize NOTIFY fontSizeChanged)
    Q_PROPERTY(double lineHeight READ getLineHeight WRITE setLineHeight NOTIFY lineHeightChanged)
    Q_PROPERTY(qint32 numLines READ getNumLines WRITE setNumLines NOTIFY numLinesChanged)
    QML_ELEMENT

public:
    DebugConsole(QQuickItem *parent = nullptr);
    ~DebugConsole();

    QColor getColor() const;
    void setColor(const QColor &color);
    qint32 getFontSize() const;
    void setFontSize(const qint32 &fontSize);
    double getLineHeight() const;
    void setLineHeight(const double &lineHeight);
    qint32 getNumLines() const;
    void setNumLines(const qint32 &numLines);

    void writeLine(QString line);
    virtual void paint(QPainter *paqint32er);

signals:
    void colorChanged();
    void fontSizeChanged();
    void lineHeightChanged();
    void numLinesChanged();
private:
    QColor color;
    double lineHeight;
    qint32 fontSize;
    qint32 numLines;
    QString* lines;
    qint32 toplineindex;
    qint32 containedlines;
};

#endif // DEBUG_CONSOLE_H
