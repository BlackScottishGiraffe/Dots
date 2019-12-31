#include "newgamewindow.h"
#include "ui_newgamewindow.h"
#include "gamefield.h"
#include "gamemaster.h"

NewGameWindow::NewGameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGameWindow)
{
    ui->setupUi(this);

}

NewGameWindow::~NewGameWindow()
{
    delete ui;
}

void NewGameWindow::setField(GameField *GF)
{
    int x,y;
    QString size = this->ui->Size->currentText();
    if(size == "Small (5x5)")
    {
        x=5;
        y=5;
    }
    else
    {
        if(size == "Medium (8x8)")
        {
            x=8;
            y=8;
        }
        else
        {
            if(size == "Large (10x10)")
            {
               x=10;
               y=10;
            }
            else
            {
               x=this->ui->Columns->value();
               y=this->ui->Rows->value();
            }
        }
    }
    GF->createField(x, y);
}

bool NewGameWindow::setFoe()
{
    return (!ui->Player->isChecked());
}

void NewGameWindow::on_Size_activated()
{
    if (ui->Size->currentText() == "Custom")
    {
        ui->Rows->setEnabled(1);
        ui->Columns->setEnabled(1);
    }
    else
    {
        ui->Rows->setDisabled(1);
        ui->Columns->setDisabled(1);
    }
}
