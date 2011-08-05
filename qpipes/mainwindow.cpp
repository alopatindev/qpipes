#include "mainwindow.h"

#include <QMessageBox>
#include <QTimer>

void MainWindow::on_aboutQtAction_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_aboutAction_triggered()
{
    QMessageBox::about(this,
                       QString::fromUtf8("Об игре «Трубопровод»"),
                       QString::fromUtf8(
"<font size=\"+1\"><b>Об игре «Трубопровод»</b></font>\
<br/><br/>\
Цель игры — соединить части трубы в единое<br/>\
целое и открыть кран, пока не истекло время.\
<br/><br/>\
Автор: Лопатин Александр © 2009"));
}

void MainWindow::on_newAction_triggered()
{
    dialog->run(gameLayout->getWidth(), gameLayout->getHeight());
}

void MainWindow::startNewGame(int width, int height, bool clearField)
{
    timeLeft = width * height * 8 / (width + height);
    if (clearField)
        gameLayout->clearField();
    gameLayout->prepareField(width, height);
    openTapButton->setEnabled(true);
    timer->start(1000);
    secondPassed();
}

void MainWindow::on_quitAction_triggered()
{
    emit close();
}

void MainWindow::on_openTapButton_clicked()
{
    openTapButton->setEnabled(false);
    timer->stop();
    checker->start(500);
}

void MainWindow::gameStop()
{
    gameLayout->holdField();
    checker->stop(); timer->stop();
    openTapButton->setEnabled(false);
}

void MainWindow::win()
{
    QMessageBox::information(this,
                             QString::fromUtf8("Удача"),
                             QString::fromUtf8("Вы выиграли!"));
    gameStop();
}

void MainWindow::fail()
{
    QMessageBox::information(this,
                             QString::fromUtf8("Неудача"),
                             QString::fromUtf8("Вы проиграли!"));
    gameStop();
}

void MainWindow::secondPassed()
{
    if (timeLeft > 59)
    {
        int minutes = timeLeft / 60;
        int seconds = timeLeft - minutes * 60;
        timeLabel->setText(QString(minutes < 10 ? "0" : "") +
                           QString::number(minutes) +
                           QString(seconds < 10 ? ":0" : ":") +
                           QString::number(seconds));
    } else {
        timeLabel->setText(QString(timeLeft < 10 ? "00:0" : "00:") +
                           QString::number(timeLeft));
    }

    if (timeLeft != 0)
        --timeLeft;
    else
        emit fail();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();

    if (checker->isActive() || timer->isActive()) {
        if (QMessageBox::question(
                this,
                QString::fromUtf8("Подтверждение выхода"),
                QString::fromUtf8("Игра еще не закончена. Выйти?"),
                QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
            checker->stop(); timer->stop();
            qApp->quit();
        }
    } else {
        checker->stop(); timer->stop();
        qApp->quit();
    }

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    showMaximized();

    gameLayout = new GameLayout(scrollAreaWidgetContents);
    dialog = new NewGameDialog(this);
    timer = new QTimer(this);
    checker = new QTimer(this);

    connect(dialog, SIGNAL(newGame(int, int)),
            this, SLOT(startNewGame(int, int)));

    connect(checker, SIGNAL(timeout()),
            gameLayout, SLOT(checkStep()));
    connect(timer, SIGNAL(timeout()),
            this, SLOT(secondPassed()));
    connect(dialog, SIGNAL(newGame(int, int)),
            checker, SLOT(stop()));
    connect(gameLayout, SIGNAL(win()),
            this, SLOT(win()));
    connect(gameLayout, SIGNAL(fail()),
            this, SLOT(fail()));

    startNewGame(DEFAULT_WIDTH, DEFAULT_HEIGHT, false);
}

MainWindow::~MainWindow()
{
    delete gameLayout;
    delete dialog;
    delete timer;
    delete checker;
}
