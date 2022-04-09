#include "debugconsole.h"
#include <QPainter>

DebugConsole::DebugConsole(QQuickItem *parent) :
    QQuickPaintedItem(parent),
    toplineindex(0),
    numlines(0)
{
    writeLine("Hello");
    writeLine("World");
}

void DebugConsole::writeLine(QString line) {
    lines[(toplineindex + numlines) % DEBUG_CONSOLE_LINE_COUNT] = line;
    numlines += numlines < 10;
    toplineindex += numlines < 10;
    emit consoleTextChanged();
}

void DebugConsole::paint(QPainter *painter)
{
    painter->drawRect(100, 100, 700, 700);
}
