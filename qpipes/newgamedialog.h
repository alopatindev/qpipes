#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include "ui_newgamedialog.h"

class NewGameDialog : public QDialog, Ui::NewGameDialog
{
    Q_OBJECT

public:
    void run(int width = 10, int height = 10);

    NewGameDialog(QWidget *parent = 0);
    ~NewGameDialog();

signals:
    void newGame(int width, int height);
};

#endif
