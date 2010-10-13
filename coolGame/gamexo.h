#ifndef GAMEXO_H
#define GAMEXO_H
#include "cell.h"
#include "gameai.h"

class GameXO
{
public:
    GameXO();
    GameXO(int Size);
    void player1StepAuto();
    void player2StepAuto();
    bool player1Step(Cell point);
    bool player2Step(Cell point);
    bool getGameState();
    int  getGameSize();
    bool getPlayer1Win();
    bool getPlayer1Status();
    GameList getPlayerList(int i);
    bool inPlayground(Cell point);
    FinLine getFinLine();

private:
    FinLine line;
    GameList listPlayer1, listPlayer2, combiList;
    int gameSize;
    void checkWin(GameList *mylist, GameList *oponentList, Cell point);
    void finishLine(Cell point, int ruleX, int ruleY, int move);
    void finishLine(Cell point, int ruleX, int ruleY);
    bool gameState;
    bool player1Win;
    bool player1Play;
    void addPosibleCell(Cell point, GameList *cobmiList_temp);
    void initGame(int i);
    void autoStep(GameList *myList, GameList *oponentList);
    bool playerStep(GameList *myList, GameList *oponentList, Cell point);
    GameList posibleSteps();

};

#endif // GAMEXO_H
