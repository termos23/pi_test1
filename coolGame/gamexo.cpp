#include "gamexo.h"

GameXO::GameXO()
{
    initGame(10);
}
GameXO::GameXO(int Size)
{
    initGame(Size);
}
int GameXO::getGameSize()
{
    return gameSize;
}
bool GameXO::getPlayer1Status()
{
    return player1Play;
}

GameList GameXO::getPlayerList(int i)
{
    if (i==1)
        return listPlayer1; //сюда бы Swith -case
    if (i==2)
        return listPlayer2;
    GameList temp; //тут чесно незнаю что делать - покамись возвращаю пустой список
    temp.clear();
    return temp;
}

void GameXO::initGame(int i)
{
    gameSize=i;
    player1Play=true;
    gameState=true;
    player1Win=false;
    listPlayer2.clear();
    listPlayer1.clear();
    combiList.clear();
    line.visible=false;

}
bool GameXO::player1Step(Cell point)
{
    if (playerStep(&listPlayer1,&listPlayer2,point)){
        player1Play=false;
        return true;
    } else
        return false;
}
bool GameXO::player2Step(Cell point)
{
    if (playerStep(&listPlayer2,&listPlayer1,point)){
        player1Play=true;
    return true;
    } else
        return false;
}
void GameXO::player1StepAuto()
{
    autoStep(&listPlayer1,&listPlayer2);
    player1Play=false;
}
void GameXO::player2StepAuto()
{
    autoStep(&listPlayer2,&listPlayer1);
    player1Play=true;
}

bool GameXO::playerStep(GameList *myList, GameList *oponentList, Cell point)
{
    if (gameState) {  //проверяем идёт ли игра вообще
        combiList.clear();
        combiList = posibleSteps();
        if (combiList.empty()){
            myList->append(point);
            checkWin(myList,oponentList,point);
            return true;
        }
    else
     if (combiList.contains(point)){
        myList->append(point);
        checkWin(myList,oponentList,point);
        return true;
        };
    return false;
    } else
    return false;
}
void GameXO::checkWin(GameList *myList, GameList *oponentList, Cell point)
{
    GameAI game(gameSize);
    // проверка на разрыв. я незнаю как эту комбинацию записать в цикл
    {
    int move;
    move=game.countAdjacentCells(point,-1,0,myList,oponentList,true,5,false);
    if (move+game.countAdjacentCells(point,1,0,myList,oponentList,true,5,false)>=4){
        gameState=false;
        finishLine(point, 1,0,move);
    };
    move=game.countAdjacentCells(point,0,-1,myList,oponentList,true,5,false);
    if (move+game.countAdjacentCells(point,0,1,myList,oponentList,true,5,false)>=4) {
        gameState=false;
        finishLine(point, 0,1,move);
    };
    move=game.countAdjacentCells(point,-1,-1,myList,oponentList,true,5,false);
    if (move+game.countAdjacentCells(point,1,1,myList,oponentList,true,5,false)>=4){
        gameState=false;
        finishLine(point, 1,1,move);
    };
    move=game.countAdjacentCells(point,-1,1,myList,oponentList,true,5,false);
    if (move+game.countAdjacentCells(point,1,-1,myList,oponentList,true,5,false)>=4) {
        gameState=false;
        finishLine(point, 1,-1,move);
    };
    }

    for (int i=-1; i<=1;i++)
     for (int j=-1; j<=1;j++)
       if (!((i==0)&&(j==0)))
          if (game.countAdjacentCells(point,i,j,myList,oponentList,true,5,false)>=4) {
            gameState=false; // глубина 5 ячеек, рядом должно быть 4
            finishLine(point, i,j);
          };
          player1Win=player1Play;

}
void GameXO::finishLine(Cell point, int ruleX, int ruleY, int step)
{
    point.x=point.x-step;
    point.y=point.y-step;
    finishLine(point,ruleX,ruleY);
}
void GameXO::finishLine(Cell point, int ruleX, int ruleY)
{
    line.point=point;
    line.ruleX=ruleX;
    line.ruleY=ruleY;
    line.visible=true;
}
FinLine GameXO::getFinLine()
{
    return line;
}

GameList GameXO::posibleSteps()
{
    GameList tempList, playersList;
    tempList.clear();
    Cell tempCell;
    for (int a=1;a<=2;a++){
        playersList=getPlayerList(a);
        if (!playersList.isEmpty()){
            foreach (Cell point, playersList){
                for (int x=-1; x<=1;x++)
                    for (int y=-1; y<=1;y++)
                        if (!((x==0)&&(y==0))){
                            tempCell.x=point.x+x;
                            tempCell.y=point.y+y;
                            addPosibleCell(tempCell, &tempList);
                        };

            }
        }
     }
return tempList;
}
void GameXO::addPosibleCell(Cell point, GameList *cobmiList_temp)
{
    if (!(listPlayer1.contains(point))&&(!listPlayer2.contains(point))&&!cobmiList_temp->contains(point)&&inPlayground(point))
        cobmiList_temp->append(point);
}

bool GameXO::inPlayground(Cell point)
{
    if (((point.x>0)&&(point.x<=gameSize))&&((point.y>0)&&(point.y<=gameSize)))
        return true;
    else
        return false;
}

void GameXO::autoStep(GameList *myList, GameList *oponentList)
{
    Cell  maxPoint;
    combiList.clear();
    combiList = posibleSteps();
    if (combiList.empty()){ // ходим первыми
        maxPoint.x=gameSize/2;
        maxPoint.y=gameSize/2;
    } else {
    int ves;
    GameAI game(gameSize);
    maxPoint=combiList.first();
    int maxVes=game.calculareWeight(myList,oponentList,maxPoint);
    foreach (Cell point, combiList){
        ves=game.calculareWeight(myList,oponentList,point);
        if (ves>maxVes) {
            maxPoint=point;
            maxVes=ves;
        };
     };
    };
    playerStep(myList, oponentList, maxPoint);
}
bool GameXO::getGameState()
{
    return gameState;
}

bool GameXO::getPlayer1Win()
{
    return player1Win;
}
