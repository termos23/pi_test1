#include "widget.h"
#include "ui_widget.h"
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QInputDialog>
#include <QMainWindow>
//#include "gameengine.h"
#include <QMessageBox>
#include <QtGui/QAbstractButton>
#include <qevent.h>

Widget::Widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QAction *quit = new QAction("&Quit", this);
    QAction *newGame = new QAction("&New game", this);
    QAction *playerPlayerMenu = new QAction("Plaeyr1-Player2", this);
    QAction *playerCompMenu = new QAction("Player1-Computer2", this);
    QAction *compPlayerMenu = new QAction("Computer1-Player2", this);
    QAction *compCompMenu = new QAction("Computer1-Computer2", this);

    QMenu *file;
    file = menuBar()->addMenu("&File");
    file->addAction(newGame);
    file->addAction(quit);
    QMenu *gameTypeMenu;
    gameTypeMenu = menuBar()->addMenu("&Game Type");
    gameTypeMenu->addAction(playerPlayerMenu);
    gameTypeMenu->addAction(playerCompMenu);
    gameTypeMenu->addAction(compPlayerMenu);
    gameTypeMenu->addAction(compCompMenu);
    connect(newGame, SIGNAL(triggered()), this, SLOT(newGame()));
    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(playerPlayerMenu, SIGNAL(triggered()), this, SLOT(changePlayerPlayer()));
    connect(playerCompMenu, SIGNAL(triggered()), this, SLOT(changePlayerComp()));
    connect(compPlayerMenu, SIGNAL(triggered()), this, SLOT(changeCompPlayer()));
    connect(compCompMenu, SIGNAL(triggered()), this, SLOT(changeCompComp()));
    game = GameXO(10);
    gameOverMesageShowed=false;
    gameType=playerComp;

}
void Widget::changePlayerPlayer()
{
    gameType=playerPlayer;
}
void Widget::changePlayerComp()
{
    gameType=playerComp;
}
void Widget::changeCompPlayer()
{
    gameType=compPlayer;
    if (game.getPlayer1Status())
        game.player1StepAuto();
}
void Widget::changeCompComp()
{
    gameType=compComp;
}



Widget::~Widget()
{
    delete ui;
}
void Widget::mousePressEvent(QMouseEvent *event)
{
   if (game.getGameState())
     if (event->buttons() && Qt::LeftButton){
       QPoint eventTemp=event->pos();
       eventTemp.setY(eventTemp.y()-20); //костыль на 20 пикселей
       GamePainter gamePainter;
        switch (gameType) {

        case playerComp:   if (game.getPlayer1Status())
                                if ( game.player1Step(gamePainter.fromXYtoHUA(eventTemp.x(),eventTemp.y(), this->width(), this->height()-20,game)))
                                      game.player2StepAuto();
                           break;
        case playerPlayer: if (game.getPlayer1Status())
                                game.player1Step(gamePainter.fromXYtoHUA(eventTemp.x(),eventTemp.y(), this->width(), this->height()-20,game));
                           else
                                game.player2Step(gamePainter.fromXYtoHUA(eventTemp.x(),eventTemp.y(), this->width(), this->height()-20,game));
                           break;
        case compComp:  {
                                game.player1StepAuto();
                                game.player2StepAuto();
                            break;
                        }
        case compPlayer:   if (game.getPlayer1Status())
                                game.player1StepAuto();
                           else
                            if (game.player2Step(gamePainter.fromXYtoHUA(eventTemp.x(),eventTemp.y(), this->width(), this->height()-20,game)))
                                game.player1StepAuto();
                           break;

        }

    };

    if (!game.getGameState()) {
        if (!gameOverMesageShowed) {
            if (game.getPlayer1Win())
                QMessageBox::warning(this, "game over", "X win");
            else
                QMessageBox::warning(this, "game over", "O win");
        gameOverMesageShowed=true;
        }
    };
    repaint();
};
void Widget::beginGame(int size)
{
    game = GameXO(size);
    gameOverMesageShowed=false;
}

void Widget::newGame()
{
    bool ok;
    int d = QInputDialog::getInt(this, tr("Playground size"),tr("Size:"), 1, 10, 100, 1, &ok);
    if (ok)
        beginGame(d);
}
void Widget::paintEvent(QPaintEvent *e)
{
// рисуем с двойным буфером
    doubleBuffer = new QPixmap(this->width(), this->height()-20);
    QPainter painter(this);
    QPainter dbPainter(doubleBuffer);
    dbPainter.eraseRect(0, 0, this->width(), this->height()-20);
    GamePainter gamePainter;
    gamePainter.drowGame(&dbPainter,this->width(), this->height()-20, game);
    painter.drawPixmap(0, 20, *doubleBuffer, 0, 0, this->width(), this->height()-20);
//ухаха, килем пейнтеров
    painter.end();
    dbPainter.end();
}
