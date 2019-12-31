#include "linebutton.h"

#include <QWidget>

lineButton::lineButton(QWidget *parent) : QPushButton(parent), isUsed(0), isVertical(0), row(0), column(0)
{
    connect(this, SIGNAL(clicked()), SLOT(click()));
    QPixmap pixmapInactive(":/resources/inactiveLine.png");
    QIcon ButtonIcon(pixmapInactive);
    this->setIcon(ButtonIcon);
    this->setIconSize(pixmapInactive.rect().size());
    this->setFlat(1);
}

void lineButton::click()
{
    isUsed = true;
    emit moveMade(row, column);
}
void lineButton::setVertical()
{
    isVertical = true;
    QPixmap pixmap(":/resources/inactiveVLine.png");
    QIcon ButtonIcon(pixmap);
    this->setIcon(ButtonIcon);
    this->setIconSize(pixmap.rect().size());
    this->setFlat(1);
}

void lineButton::setPosition(int x, int y)
{
     row = x;
     column = y;
}

int lineButton::getRow()
{
    return row;
}
int lineButton::getColumn()
{
    return column;
}
void lineButton::paint(int x, int y, bool playerMove)
{
    if(row != x || column != y)
        return;
    QPixmap pm;
    if(!playerMove)
    {
        if(isVertical)
        {
            pm.load(":/resources/blueVLine.png");
        }
        else
        {
            pm.load(":/resources/blueLine.png");
        }
    }
    else
    {
        if(isVertical)
        {
            pm.load(":/resources/orangeVLine.png");
        }
        else
        {
            pm.load(":/resources/orangeLine.png");
        }
    }
    QIcon ButtonIcon(pm);
    this->setIcon(ButtonIcon);
    this->setFlat(1);
    this->setIconSize(pm.rect().size());
}
