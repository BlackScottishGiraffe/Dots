#ifndef NEWGAMEWINDOW_H
#define NEWGAMEWINDOW_H

#include "gamefield.h"
#include "ai.h"

#include <QDialog>

namespace Ui
{
    class NewGameWindow;
}

class NewGameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewGameWindow(QWidget *parent = nullptr);
    ~NewGameWindow();
    void setField(GameField*);
    bool setFoe();

private:
    Ui::NewGameWindow *ui;

private slots:
    void on_Size_activated();
};

#endif // NEWGAMEWINDOW_H
