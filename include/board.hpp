#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>
#include "types.hpp"

class Token;
class Player;

class Board {
private:
    bool safeCell[TRACK_LENGTH];  
    int startCells[4];   

    std::string cellText(int cell, const Player players[], int numPlayers) const;
    void drawTrack(const Player players[], int numPlayers) const;

public:
    Board();                    
    ~Board();               

    Board& markSafe(int cell);  
    bool isSafe(int cell) const;
    int getStartCell(int colour) const;

    int checkCapture(const Token& mover, Player players[], int numPlayers) const;

    void display() const;      
    void display(const Player& player) const;                    
    void display(const Player players[], int numPlayers) const; 

    friend std::ostream& operator<<(std::ostream& out, const Board& board);
};

#endif