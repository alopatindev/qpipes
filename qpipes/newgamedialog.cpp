#include "newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
}

NewGameDialog::~NewGameDialog()
{
}

void NewGameDialog::run(int width, int height)
{
    widthSpin->setValue(width);
    heightSpin->setValue(height);

    if (exec() == QDialog::Accepted)
        emit newGame(widthSpin->text().toInt(),
                     heightSpin->text().toInt());
}
