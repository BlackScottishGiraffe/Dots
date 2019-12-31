#include "fieldsquare.h"

FieldSquare::FieldSquare(QWidget *parent) : QPushButton(parent), row(0), column(0)
{
    QPixmap pixmap(":/resources/inactiveSqr.png");
    QIcon ButtonIcon(pixmap);
    this->setIcon(ButtonIcon);
    this->setFlat(1);
}

void FieldSquare::setPosition(int x, int y)
{
     row = x;
     column = y;
}

void FieldSquare::setColor(int x, int y, bool color)
{
    if (x != row || y != column)
        return;
    QPixmap pm;
    if(!color)
        pm.load(":/resources/blueSqr.png");
    else
        pm.load(":/resources/orangeSqr.png");
    QIcon ButtonIcon(pm);
    this->setIcon(ButtonIcon);
}

