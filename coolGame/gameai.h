#ifndef GAMEAI_H
#define GAMEAI_H
#include "cell.h"
#include "stdlib.h"
#include "time.h"

class GameAI
{
public:
    GameAI(int size);
    int calculareWeight(GameList *myList, GameList *oponentList,  Cell point);
    bool checkCell(Cell point, GameList *list);
    int countAdjacentCells(Cell point, int dX, int dY, GameList *myList, GameList *oponentList, bool findBrothers, int deep, bool bothEnds);

private:
    int gameSize;
    bool inPlayground(Cell point);
    int countAdjacentCells(Cell point, int dX, int dY, GameList *myList, GameList *oponentList, bool findBrothers, int deep);
};

#endif // GAMEAI_H
