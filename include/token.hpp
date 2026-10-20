#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <iostream>
#include "Position.hpp"

enum class TokenState {
    HOME,
    ACTIVE,
    FINISHED
};

class Token {
private:
    int id;
    int colour;
    TokenState state;
    int stepsTaken;
    Position pos;

public:
    Token();
    Token(int id, int colour);

    void leaveHome();
    Token& move(int steps);
    Token& move(int steps, bool extraTurn);

    Token& operator++();

    void sendHome();
    void finish();

    TokenState getState() const;
    int getCell() const;
    int getSteps() const;
    int getId() const;
    int getColour() const;

    friend std::ostream& operator<<(std::ostream& out,const Token& token);
};
#endif
