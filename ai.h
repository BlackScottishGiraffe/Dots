#ifndef AI_H
#define AI_H

#include <QObject>

class AI : public QObject
{
    Q_OBJECT
private:
    bool isEnabled;
public:
    explicit AI(QObject *parent = nullptr);
    void enable(bool);
public slots:
    void getInfo(QVector<int>,QVector<int>);
signals:
    void makeMove(int,int);
};

#endif // AI_H
