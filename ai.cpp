#include "ai.h"

#include <QRandomGenerator>
#include <QVector>

AI::AI(QObject *parent) : QObject(parent), isEnabled(false)
{

}

void AI::enable(bool activate)
{
    isEnabled = activate;
}

void AI::getInfo(QVector<int> a, QVector<int> b)
{
    if(isEnabled)
    {
        if(a.size() == 0)
            return;
        QRandomGenerator rand;
        int i = rand.bounded(0,a.size());
        emit makeMove(a[i],b[i]);
    }
}

