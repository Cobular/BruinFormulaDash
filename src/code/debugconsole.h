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
    DebugConsole(const DebugConsole& src) {
        numLines = src.numLines;
        lines = new QString[src.numLines];
        for (int i = 0; i < numLines; i++) {
            lines[i] = src.lines[i];
        }
        this->toplineindex = src.toplineindex;
        this->containedlines = src.containedlines;
        this->color = src.color;
        this->lineHeight = src.lineHeight;
        this->fontSize = src.fontSize;
    }
    const DebugConsole& operator=(const DebugConsole& src) {
        delete [] lines;
        numLines = src.numLines;
        lines = new QString[src.numLines];
        for (int i = 0; i < numLines; i++) {
            lines[i] = src.lines[i];
        }
        this->toplineindex = src.toplineindex;
        this->containedlines = src.containedlines;
        this->color = src.color;
        this->lineHeight = src.lineHeight;
        this->fontSize = src.fontSize;
    }
    ~DebugConsole() {
        delete [] lines;
    }
    void writeLine(QString line);
    virtual void paint(QPainter *paqint32er);

    QColor getColor() const {
        return color;
    }
    void setColor(const QColor &color) {
        if (this->color != color) {
            this->color = color;
            emit colorChanged();
        }
    }

    qint32 getFontSize() const {
        return fontSize;
    }
    void setFontSize(const qint32 &fontSize) {
        if (this->fontSize != fontSize) {
            this->fontSize = fontSize;
            emit fontSizeChanged();
        }
    }

    double getLineHeight() const {
        return lineHeight;
    }
    void setLineHeight(const double &lineHeight) {
        if (this->lineHeight != lineHeight) {
            this->lineHeight = lineHeight;
            emit lineHeightChanged();
        }
    }

    qint32 getNumLines() const {
        return numLines;
    }
    void setNumLines(const qint32 &numLines) {
        if (numLines == this->numLines) return;
        qint32 numitemstocopy = numLines < containedlines ? numLines : containedlines;
        qint32 firstitemtocopy = toplineindex + containedlines - numitemstocopy;
        QString* newlines = new QString[numLines];
        for (int i = 0; i < numitemstocopy; i++) {
            newlines[i] = lines[(firstitemtocopy + i) % this->numLines];
        }
        delete [] lines;
        lines = newlines;
        toplineindex = 0;
        containedlines = numitemstocopy;
        this->numLines = numLines;
        emit numLinesChanged();
    }
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
