#include <iostream>
#include "token.hpp"
#include "types.hpp"

Token::Token(): id(0), colour(0), state(TokenState::HOME), stepsTaken(0), pos() {}

Token::Token(int id, int colour): id(id), colour(colour), state(TokenState::HOME), stepsTaken(0), pos() {}

void Token::leaveHome() {
    if (state != TokenState::HOME) return;
    int startCell = (colour % 4) * 13;
    pos = Position(startCell);
    stepsTaken = 0;
    state = TokenState::ACTIVE;
}

Token& Token::move(int steps) {
    return move(steps, false);
}

Token& Token::move(int steps, bool extraTurn) {
    (void)extraTurn;
    if (state != TokenState::ACTIVE || steps < 0) return *this;
    if (stepsTaken + steps > FINISH_STEP) return *this;     

    stepsTaken += steps;
    if (stepsTaken == FINISH_STEP) {
        pos = Position(HOME_COLUMN_LENGTH - 1, true);
        finish();
    } else if (stepsTaken > LAST_TRACK_STEP) {             
        pos = Position(stepsTaken - LAST_TRACK_STEP - 1, true);
    } else {
        pos = pos + steps;                                  
    }
    return *this;
}

Token& Token::operator++() { return move(1); }

void Token::sendHome() {
    state = TokenState::HOME;
    stepsTaken = 0;
    pos = Position();
}

void Token::finish() {
    if (state == TokenState::ACTIVE) state = TokenState::FINISHED;
}

TokenState Token::getState() const { return state; }
int Token::getCell() const { return pos.getCell(); }
int Token::getSteps() const { return stepsTaken; }
int Token::getId() const { return id; }
int Token::getColour() const { return colour; }
bool Token::isInHomeColumn() const { return pos.isInHomeColumn(); }  

std::ostream& operator<<(std::ostream& out, const Token& token) {
    out << "T" << token.id << ": ";
    if (token.state == TokenState::HOME) out << "HOME";
    else if (token.state == TokenState::FINISHED) out << "FINISHED";
    else out << token.pos << " (steps " << token.stepsTaken << ")";
    return out;
}