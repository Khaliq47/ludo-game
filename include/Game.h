#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Dice.h"
#include "Player.h"

class Game {
private:
    Board board;
    Dice dice;
    Player* players;
    int numPlayers;
    int turn;

    void moveToken(Player& p, int idx, int roll);

public:
    Game();
    Game(int n);
    ~Game();

    void setup();
    void run();
    Player& getPlayer(int i);
    void showStatus() const;
    void declareWinner() const;
};

#endif
