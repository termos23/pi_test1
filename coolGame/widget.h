#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include "gamexo.h"
#include "gamepainter.h"
#include "cell.h"

namespace Ui {
    class Widget;
}

class Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    GameXO game;
    QPixmap *doubleBuffer;
    bool gameOverMesageShowed;
    enum gameTypes {playerPlayer,playerComp,compPlayer,compComp};
    unsigned gameType;


private:
    void beginGame(int);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);
private slots:
    void newGame();
    void changePlayerPlayer();
    void changePlayerComp();
    void changeCompPlayer();
    void changeCompComp();




};

#endif // WIDGET_H
