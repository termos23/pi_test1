#include "gameai.h"

GameAI::GameAI(int size)
{
    gameSize=size;
}
int GameAI::countAdjacentCells(Cell point, int dX, int dY, GameList *myList, GameList *oponentList, bool findBrothers, int deep)
{

    int count=0;
    Cell myPoint;
    GameList tempList;
    if (findBrothers)
        tempList=*myList;
    else
        tempList=*oponentList;
    myPoint.x=point.x+dX;
    myPoint.y=point.y+dY;
    while (checkCell(myPoint, &tempList)&&(count!=deep)){
        count++; //рядом наш
        myPoint.x=myPoint.x+dX;
        myPoint.y=myPoint.y+dY;
    };
    return count;
}
int GameAI::countAdjacentCells(Cell point, int dX, int dY, GameList *myList, GameList *oponentList, bool findBrothers, int deep, bool bothEnds)
{

    int count=0;
    if (bothEnds){
        count=countAdjacentCells(point,dX,dY, myList, oponentList, findBrothers, deep);
        count+=countAdjacentCells(point,-dX,-dY, myList, oponentList, findBrothers, deep);
    } else
        count=countAdjacentCells(point,dX,dY, myList, oponentList, findBrothers, deep);
    return count;
}
bool GameAI::checkCell(Cell point, GameList *list)
{
    if (inPlayground(point)&&list->contains(point))
        return true;
    else
        return false;
}
bool GameAI::inPlayground(Cell point)
{
    if (((point.x>0)&&(point.x<=gameSize))&&((point.y>0)&&(point.y<=gameSize)))
        return true;
    else
        return false;
}

int GameAI::calculareWeight(GameList *myList, GameList *oponentList, Cell point)
{
    srand ( time(NULL) );
    for (int i=-1; i<=1;i++)
     for (int j=-1; j<=1;j++)
       if (!((i==0)&&(j==0)))
           if (countAdjacentCells(point,i,j,myList,oponentList,true,5,false)>=4)
               return 5; // глубна 5 ячеек, рядом должно быть 4

    bool temp;
    for (int a=1;a<=2;a++){
        if (a==1)
            temp=true;
        else
            temp=false;
        if (countAdjacentCells(point,-1,0,myList,oponentList,temp,5,true)>=4)
            return 5;
        if (countAdjacentCells(point,0,-1,myList,oponentList,temp,5,true)>=4)
            return 5;
        if (countAdjacentCells(point,-1,-1,myList,oponentList,temp,5,true)>=4)
            return 5;
        if (countAdjacentCells(point,-1,1,myList,oponentList,temp,5,true)>=4)
            return 5;
    }

    for (int a=3;a>=2;a--)
     for (int i=-1; i<=1;i++)
      for (int j=-1; j<=1;j++)
        if (!((i==0)&&(j==0)))
          if (countAdjacentCells(point,i,j,myList,oponentList,false,a+1,false)>=a)
             return a+1;

    int min = countAdjacentCells(point,((rand()%3)-1),((rand()%3)-1),myList,oponentList,true,5,false) ;
    for (int i=-1; i<=1;i++)
     for (int j=-1; j<=1;j++)
       if ((i!=0)&&(j!=0))
         if (countAdjacentCells(point,i,j,myList,oponentList,true,5,false)>min)
            min=countAdjacentCells(point,i,j,myList,oponentList,true,5,false);
     return min;
}
