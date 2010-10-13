#ifndef GAMEPAINTER_H
#define GAMEPAINTER_H
#include "cell.h"
#include <QPainter>
#include "gamexo.h"
class GamePainter
{
    //HUA - Human Understanding Adress
public:
    GamePainter();
    Cell fromXYtoHUA(int x, int y, int width, int height, GameXO game);
    int fromHUAtoX(Cell point, int width, int height);
    int fromHUAtoY(Cell point, int width, int height);
    void drowGame(QPainter *painter, int  width, int height, GameXO game);
private:
    int stepX, stepY, gameSize;
    void drowXO(QPainter *painter, bool drowX, Cell point, int width, int height);
    void drowGrid(QPainter *painter, int width, int height);
    void drowLine(QPainter *painter, FinLine line,  int width, int height);

};

#endif // GAMEPAINTER_H
