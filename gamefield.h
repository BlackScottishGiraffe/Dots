#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>

#include "gamemaster.h"
#include "linebutton.h"
#include "ai.h"

namespace Ui {
class GameField;
}

class GameField : public QWidget
{
    Q_OBJECT
private:
    Ui::GameField *ui;
    GameMaster GM;
    int p1,p2;
    bool vsAI;
public:
    explicit GameField(QWidget *parent = nullptr);
    ~GameField();
    void createField(int x, int y);
    void loadPrevGame();
    void activateAI(AI*);
public slots:
    void changeMove();
    void addPoint(bool playerMove);
    void endgame();
    void reconstruct(int,int);
signals:
    void restart();
    void exit();
};

#endif // GAMEFIELD_H
