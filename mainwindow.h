#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamefield.h"
#include "ai.h"

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    AI BOT;
    GameField GF;
    Ui::MainWindow *ui;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void startNewGame();
    void continueGame();
    void displayAbout();
    void exit();
};

#endif // MAINWINDOW_H
