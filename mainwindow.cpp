#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newgamewindow.h"
#include "gamefield.h"

#include <QMessageBox>
#include <QFile>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&GF,SIGNAL(restart()),this,SLOT(startNewGame()));
    connect(&GF,SIGNAL(exit()),this,SLOT(exit()));
    QFile load("D:/Kurs/Dots/savedgame.bin");
    if(load.exists())
    {
        ui->continue_2->setEnabled(1);
        ui->actionContinue_Last_Game->setEnabled(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startNewGame()
{
    BOT.enable(false);
    NewGameWindow ngw(this);
    ngw.show();
    if (ngw.exec() == NewGameWindow::Accepted)
    {
        ngw.setField(&GF);
        if(ngw.setFoe())
        {
           BOT.enable(true);
           GF.activateAI(&BOT);
        }

    }
    GF.show();
    this->hide();
}

void MainWindow::continueGame()
{
    GF.loadPrevGame();
    QMessageBox box;
    box.setText("Continue game with Computer or Player 2?");
    box.addButton("Player 2", QMessageBox::YesRole);
    box.addButton("Computer", QMessageBox::NoRole);
    if (box.exec() == QMessageBox::NoRole)
    {
        BOT.enable(true);
        GF.activateAI(&BOT);
    }
    GF.show();
    this->hide();
}

void MainWindow::displayAbout()
{
    QMessageBox about;
    about.setWindowTitle(tr("About Dots"));
    about.setIcon(QMessageBox::Information);
    about.setText(tr("Author: Maxim Perevoznikov, 2019"));
    about.exec();
}

void MainWindow::exit()
{
    QCoreApplication::quit();
}
