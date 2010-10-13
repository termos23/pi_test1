#include "gamepainter.h"

GamePainter::GamePainter()
{
    stepX=0;
    stepY=0;
    gameSize=0;
}
Cell GamePainter::fromXYtoHUA(int x, int y, int width, int height, GameXO game)
{
  Cell result;
  y=height-y; // переворачиваем y
  result.x=((x*game.getGameSize())/width)+1;
  result.y=((y*game.getGameSize())/(height))+1;
  return result;

}
void GamePainter::drowGame(QPainter *painter, int width, int height, GameXO game)
{
    gameSize=game.getGameSize();
    drowGrid(painter,width,height);
    stepX=width/gameSize;
    stepY=width/gameSize;
    Cell tempcell;
    foreach( tempcell,game.getPlayerList(1)) // берём Х
        drowXO(painter,true,tempcell,width,height);
    foreach( tempcell,game.getPlayerList(2)) //берём О
        drowXO(painter,false,tempcell,width,height);
    drowLine(painter, game.getFinLine(), width,height);

}
void GamePainter::drowXO(QPainter *painter, bool drowX, Cell point, int width, int height)
{
    painter->setPen(Qt::black);                         //цвет кисти
    if (drowX) {
        painter->drawLine(fromHUAtoX(point,width,height),fromHUAtoY(point,width,height),fromHUAtoX(point,width,height)+stepX,fromHUAtoY(point,width,height)+stepY);
        painter->drawLine(fromHUAtoX(point,width,height),fromHUAtoY(point,width,height)+stepY,fromHUAtoX(point,width,height)+stepX,fromHUAtoY(point,width,height));
    } else
        painter->drawEllipse(fromHUAtoX(point,width,height),fromHUAtoY(point,width,height),stepX,stepY);
}

void GamePainter::drowLine(QPainter *painter, FinLine line,  int width, int height)
{
    if (line.visible)
    {
        painter->setPen(Qt::green);
        Cell point, point2;
        point=line.point;
        point2.x=line.point.x+(line.ruleX*4);
        point2.y=line.point.y+(line.ruleY*4);
        painter->drawLine(fromHUAtoX(point,width,height)+(stepX/2),fromHUAtoY(point,width,height)+(stepY/2),fromHUAtoX(point2,width,height)+(stepX/2),fromHUAtoY(point2,width,height)+(stepY/2));

    }
}

int GamePainter::fromHUAtoX(Cell point, int width, int height)
{
    return (point.x-1)*(width/gameSize);
}
int GamePainter::fromHUAtoY(Cell point, int width, int height)
{
    return height-((point.y)*(height/gameSize));
}

void GamePainter::drowGrid(QPainter *painter, int width, int height)
{
    painter->setPen(Qt::red);
    for(int i=1;i<gameSize;i++){
      //вывод горизонтальных линий
        painter->drawLine(0,i*(height/gameSize),width,i*(height/gameSize));
      //вывод вертикальных линий
        painter->drawLine((width/gameSize)*i,0,(width/gameSize)*i,height);
     }
}
