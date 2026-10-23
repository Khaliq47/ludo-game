#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "dice.hpp"
#include "player.hpp"

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