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
