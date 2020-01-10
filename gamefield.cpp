#include "gamefield.h"
#include "ui_gamefield.h"
#include "linebutton.h"
#include "fieldsquare.h"
#include "gamemaster.h"

#include <QMessageBox>

GameField::GameField(QWidget *parent) : QWidget(parent), ui(new Ui::GameField), p1(false), p2(false), vsAI(false)
{
    ui->setupUi(this);
    ui->gridLayout->setSpacing(0);
    connect(&GM,SIGNAL(addPoint(bool)),this,SLOT(addPoint(bool)));
    connect(&GM,SIGNAL(gameover()),this,SLOT(endgame()));
}

GameField::~GameField()
{
    delete ui;
}

void GameField::createField(int x, int y)
{
    GM.setField(x,y);
    for(int i=0;i<x*2-1;i++)
        for(int j=0;j<2*y-1;j++)
            if(i%2==0)
                if(j%2==0)
                {
                    QPushButton *dot = new QPushButton;
                    QPixmap pixmap(":/resources/dot.png");
                    QIcon ButtonIcon(pixmap);
                    dot->setIcon(ButtonIcon);
                    dot->setFlat(1);
                    dot->setDisabled(1);
                    dot->setIconSize(pixmap.rect().size());
                    ui->gridLayout->addWidget(dot,i,j);
                }
                else
                {
                    lineButton *butt = new lineButton;
                    butt->setPosition(i,j);
                    ui->gridLayout->addWidget(butt,i,j);
                    connect(butt,SIGNAL(moveMade(int,int)),&GM,SLOT(moveMade(int,int)));
                    connect(&GM,SIGNAL(sendPaintSignal(int, int, bool)),butt,SLOT(paint(int, int, bool)));
                    connect(&GM,SIGNAL(changeMove()),this,SLOT(changeMove()));
                }
            else
                if(j%2!=0)
                {
                    FieldSquare *sqr = new FieldSquare;
                    sqr->setPosition(i,j);
                    ui->gridLayout->addWidget(sqr,i,j);
                    connect(&GM,SIGNAL(sendPaintSignal(int,int,bool)),sqr,SLOT(setColor(int,int,bool)));
                }
                else
                {
                    lineButton *butt = new lineButton;
                    butt->setVertical();
                    butt->setPosition(i,j);
                    ui->gridLayout->addWidget(butt,i,j);
                    connect(butt,SIGNAL(moveMade(int,int)),&GM,SLOT(moveMade(int,int)));
                    connect(&GM,SIGNAL(sendPaintSignal(int, int, bool)),butt,SLOT(paint(int, int, bool)));
                    connect(&GM,SIGNAL(changeMove()),this,SLOT(changeMove()));
                }
}

void GameField::changeMove()
{
    if(vsAI)
        if(GM.returnPlayerMove())
        {
            GM.freeLines();
            ui->label->setText("AI Turn");
        }
        else
            ui->label->setText("Your Turn");
    else
        if(GM.returnPlayerMove())
            ui->label->setText("Turn: Player 2");
        else
            ui->label->setText("Turn: Player 1");
}

void GameField::addPoint(bool pm)
{
    if(!pm)
    {
        p1++;
        ui->lcdNumber->display(p1);
    }
    else
    {
        p2++;
        ui->lcdNumber_2->display(p2);
    }
}

void GameField::endgame()
{
    if(p1>p2)
        ui->label->setText("Player 1 won!");
    else
        if(p2>p1)
            ui->label->setText("Player 2 won!");
        else
            ui->label->setText("A Tie!");
    GM.deleteFile();
    QMessageBox box;
    box.setText("Gameover! Would you like to play again?");
    box.addButton(QMessageBox::Ok);
    box.addButton(QMessageBox::Close);
    if (box.exec() == QMessageBox::Ok)
        emit restart();
    else
        emit exit();
}

void GameField::loadPrevGame()
{
    connect(&GM,SIGNAL(createField(int,int)),this,SLOT(reconstruct(int,int)));
    GM.load();
    this->changeMove();
}

void GameField::reconstruct(int x, int y)
{
    this->createField(x,y);
}

void GameField::activateAI(AI *BOT)
{
    vsAI = true;
    connect(&GM,SIGNAL(sendToAI(QVector<int>,QVector<int>)),BOT,SLOT(getInfo(QVector<int>,QVector<int>)));
    connect(BOT,SIGNAL(makeMove(int,int)),&GM,SLOT(moveMade(int,int)));
    if(GM.returnPlayerMove() == true)
        GM.freeLines();
}
