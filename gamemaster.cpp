#include "gamemaster.h"
#include "linebutton.h"
#include "fieldsquare.h"

#include <QFile>
#include <QVector>

GameMaster::GameMaster() : playerMove(0), movesLeft(0)
{

}

void GameMaster::setField(int x, int y)
{
    row=x,column=y;
    arr = new element *[x*2-1];
    for (int i=0;i<x*2-1;i++)
    {
        arr[i] = new element [y*2-1];
        for(int j=0;j<y*2-1;j++)
        {
            if(i%2==0)
               if(j%2==0)
                    arr[i][j]=dot;
                else
                    {
                        arr[i][j]=line;
                        movesLeft++;
                    }
            else
                if(j%2!=0)
                    arr[i][j]=square;
                else
                {
                    arr[i][j]=line;
                    movesLeft++;
                }
        }
    }
}

bool GameMaster::returnPlayerMove()
{
    return playerMove;
}

void GameMaster::moveMade(int x, int y)
{
    if(arr[x][y] != line)
        return;
    if(!playerMove)
        arr[x][y]=blueline;
    else
        arr[x][y]=orangeline;
    emit sendPaintSignal(x,y,playerMove);
    if(!checkSquares(x,y))
        changeTurn();
    this->save();
    movesLeft--;
    if(movesLeft == 0)
        emit gameover();
}

void GameMaster::changeTurn()
{
    playerMove = !playerMove;
    emit changeMove();
}

bool GameMaster::checkSquares(int x, int y)
{
    bool toReturn = false;
    if(x!=0)
        if(checkAroundSquare(x-1,y))
            toReturn = true;
    if(y!=0)
        if(checkAroundSquare(x,y-1))
            toReturn = true;
    if(x!=row*2-2)
        if(checkAroundSquare(x+1,y))
            toReturn = true;
    if(y!=column*2-2)
        if(checkAroundSquare(x,y+1))
            toReturn = true;
    return toReturn;
}

bool GameMaster::checkAroundSquare(int x, int y)
{
    if (arr[x][y]==square)
        if(arr[x-1][y] == blueline || arr[x-1][y] == orangeline)
            if(arr[x][y-1] == blueline || arr[x][y-1] == orangeline)
                if(arr[x+1][y] == blueline || arr[x+1][y] == orangeline)
                    if(arr[x][y+1] == blueline || arr[x][y+1] == orangeline)
                    {
                        if(!playerMove)
                            arr[x][y] = bluesquare;
                        else
                            arr[x][y] = orangesquare;
                        emit sendPaintSignal(x,y,playerMove);
                        emit addPoint(playerMove);
                        return true;
                    }
    return false;
}

void GameMaster::freeLines()
{

    QVector<int> freeRows, freeColumns;
    for(int i=0;i<2*row-1;i++)
        for(int j=0;j<2*column-1;j++)
            if(arr[i][j]==line)
            {
                freeRows.push_back(i);
                freeColumns.push_back(j);
            }
    emit sendToAI(freeRows,freeColumns);

}

void GameMaster::save()
{
    QFile savefile("D:/Kurs/Dots/savedgame.bin");
    savefile.open(QIODevice::WriteOnly);
    QDataStream out(&savefile);
    out << row << column << movesLeft << playerMove;
    for(int i=0;i<row*2-1;i++)
        for(int j=0;j<column*2-1;j++)
        {
            int k;
            switch(arr[i][j])
            {
                case dot :
                    k=0;
                    break;
                case line:
                    k=1;
                    break;
                case square:
                    k=2;
                    break;
                case blueline:
                    k=3;
                    break;
                case orangeline:
                    k=4;
                    break;
                case bluesquare:
                    k=5;
                    break;
                case orangesquare:
                    k=6;
                    break;
                default:
                    k=0;
                    break;
            }
            out << k;
        }
    savefile.close();
}

void GameMaster::load()
{
    QFile savefile("D:/Kurs/Dots/savedgame.bin");
    savefile.open(QIODevice::ReadOnly);
    QDataStream in(&savefile);
    in >> row >> column >> movesLeft >> playerMove;
    emit createField(row, column);
    for(int i=0;i<row*2-1;i++)
        for(int j=0;j<column*2-1;j++)
        {
            int k;
            in >> k;
            switch(k)
            {
                case 0:
                    arr[i][j] = dot;
                    break;
                case 1:
                    arr[i][j] = line;
                    break;
                case 2:
                    arr[i][j] = square;
                    break;
                case 3:
                    arr[i][j] = blueline;
                    break;
                case 4:
                    arr[i][j] = orangeline;
                    break;
                case 5:
                    arr[i][j] = bluesquare;
                    break;
                case 6:
                    arr[i][j] = orangesquare;
                    break;
            }
            if(arr[i][j] == bluesquare || arr[i][j] == blueline)
                emit sendPaintSignal(i,j,false);
            if(arr[i][j] == bluesquare)
                emit addPoint(false);
            if(arr[i][j] == orangesquare || arr[i][j] == orangeline)
                emit sendPaintSignal(i,j,true);
            if(arr[i][j] == orangesquare)
                emit addPoint(true);
        }
    savefile.close();
}

void GameMaster::deleteFile()
{
    QFile savefile("D:/Kurs/Dots/savedgame.bin");
    savefile.remove();
}
