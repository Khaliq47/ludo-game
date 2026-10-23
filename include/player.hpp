#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "Token.h"      

class Player {
private:
    std::string name;
    int colour;                      
    Token tokens[4];                 
    int finishedCount;
    int (*chooser)(Player&, int);    

public:
    Player();                                
    Player(std::string name, int colour);
    ~Player();

    
    Player& setChooser(int (*f)(Player&, int));
    Player& setName(std::string name);

    
    Token& operator[](int i);
    const Token& operator[](int i) const;

    
    bool hasWon() const;
    void tokenFinished();
    bool canMove(int index, int roll) const;   
    bool canMoveAny(int roll) const;
    int  chooseToken(int roll);                

    
    std::string getName() const;
    int getColour() const;
    int getFinishedCount() const;
    std::string getColourName() const;

    friend std::ostream& operator<<(std::ostream& out, const Player& p);
};

#endif
