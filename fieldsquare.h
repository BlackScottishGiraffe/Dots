#ifndef FIELDSQUARE_H
#define FIELDSQUARE_H

#include <QWidget>
#include <QPushButton>

class FieldSquare : public QPushButton
{
    Q_OBJECT
public:
    explicit FieldSquare(QWidget *parent = nullptr);
    void setPosition(int x, int y);
private:
    int row, column;
signals:

public slots:
    void setColor(int x, int y, bool color);
};

#endif // FIELDSQUARE_H
