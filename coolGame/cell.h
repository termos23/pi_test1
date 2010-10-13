#ifndef CELL_H
#define CELL_H
#include <QList>
struct Cell
{
   int x;
   int y;
   bool operator==(const Cell& right)
   {
     return this->x==right.x && this->y==right.y;
   }

};
struct FinLine
{
    Cell point;
    int ruleX;
    int ruleY;
    bool visible;
};
typedef QList<Cell> GameList;
#endif // CELL_H
