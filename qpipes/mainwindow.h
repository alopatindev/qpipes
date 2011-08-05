#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "newgamedialog.h"
#include "gamelayout.h"

class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT

    GameLayout *gameLayout;
    NewGameDialog *dialog;
    QTimer *checker, *timer;
    int timeLeft;

    void gameStop();

public slots:
    void on_aboutQtAction_triggered();
    void on_aboutAction_triggered();
    void on_newAction_triggered();
    void startNewGame(int width, int height, bool clearField = true);
    void on_quitAction_triggered();
    void on_openTapButton_clicked();
    void win();
    void fail();
    void secondPassed();

protected:
    void closeEvent(QCloseEvent *event);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif
