#ifndef GAMEMASTER_H
#define GAMEMASTER_H

#include <QObject>

class GameMaster : public QObject
{
    Q_OBJECT
private:
    bool playerMove;
    enum element{dot,line,square,blueline,orangeline,bluesquare,orangesquare};
    element **arr;
    int row, column, movesLeft;
public:
    GameMaster();
    void setField(int n, int m);
    bool returnPlayerMove();
    void changeTurn();
    bool checkSquares(int i, int j);
    bool checkAroundSquare(int i, int j);
    void save();
    void load();
    void deleteFile();
    void freeLines();
public slots:
    void moveMade(int n, int m);
signals:
    void sendPaintSignal(int,int,bool);
    void addPoint(bool);
    void changeMove();
    void gameover();
    void createField(int, int);
    void sendToAI(QVector<int>,QVector<int>);
};

#endif // GAMEMASTER_H
