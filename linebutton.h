#ifndef LINEBUTTON_H
#define LINEBUTTON_H

#include <QPushButton>

class lineButton : public QPushButton
{
    Q_OBJECT
private:
    bool isUsed, isVertical;
    int row,column;
public:
    explicit lineButton(QWidget *parent = nullptr);
    void setVertical();
    void setPosition(int x, int y);
    int getRow();
    int getColumn();
signals:
    void moveMade(int x, int y);
public slots:
    void click();
    void paint(int, int, bool);
};

#endif // LINEBUTTON_H

//
