#include "debugconsole.h"
#include <QPainter>


DebugConsole::DebugConsole(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    color("green"),
    lineHeight(1.5),
    fontSize(12),
    numLines(10),
    lines(new QString[10]),
    toplineindex(0),
    containedlines(0)
{
    writeLine("BruinFormulaDash [Version 0.1]");
    writeLine("(c) BruinRacing. Open Source.");
}

DebugConsole::~DebugConsole() {
    delete [] lines;
}


QColor DebugConsole::getColor() const {
    return color;
}
void DebugConsole::setColor(const QColor &color) {
    if (this->color != color) {
        this->color = color;
        emit colorChanged();
    }
}

qint32 DebugConsole::getFontSize() const {
    return fontSize;
}
void DebugConsole::setFontSize(const qint32 &fontSize) {
    if (this->fontSize != fontSize) {
        this->fontSize = fontSize;
        emit fontSizeChanged();
    }
}

double DebugConsole::getLineHeight() const {
    return lineHeight;
}
void DebugConsole::setLineHeight(const double &lineHeight) {
    if (this->lineHeight != lineHeight) {
        this->lineHeight = lineHeight;
        emit lineHeightChanged();
    }
}

qint32 DebugConsole::getNumLines() const {
    return numLines;
}
void DebugConsole::setNumLines(const qint32 &numLines) {
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


void DebugConsole::writeLine(QString line) {
    lines[(toplineindex + containedlines) % numLines] = line;
    toplineindex += containedlines >= numLines;
    containedlines += containedlines < numLines;
    update();
}


void DebugConsole::paint(QPainter *painter)
{
    QFont f = painter->font();
    f.setPointSize(fontSize);
    painter->setFont(f);
    painter->setPen(QPen(color));
    for (int i = 0 ; i < numLines; i++) {
        painter->drawText(0, fontSize + fontSize*lineHeight*i, lines[(toplineindex + i) % numLines]);
    }
}
