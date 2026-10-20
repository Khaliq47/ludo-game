#include <iostream>
#include "Token.hpp"

Token::Token(): id(0),colour(0),state(TokenState::HOME),stepsTaken(0),pos() {}

Token::Token(int id, int colour): id(id),colour(colour),state(TokenState::HOME),stepsTaken(0),pos() {}

void Token::leaveHome() {
    if (state != TokenState::HOME) {
        return;
    }

    // Assumes colours 0, 1, 2, 3 map to starts
    // 0, 13, 26, 39 respectively.
    int startCell = (colour % 4) * 13;

    pos = Position(startCell);
    stepsTaken = 0;
    state = TokenState::ACTIVE;
}

Token& Token::move(int steps) {
    return move(steps, false);
}

Token& Token::move(int steps, bool extraTurn) {
    (void)extraTurn; // Turn management belongs to Game.

    if (state != TokenState::ACTIVE || steps < 0) {
        return *this;
    }

    pos = pos + steps;
    stepsTaken += steps;

    return *this;
}

Token& Token::operator++() {
    return move(1);
}

void Token::sendHome() {
    state = TokenState::HOME;
    stepsTaken = 0;
    pos = Position();
}

void Token::finish() {
    if (state == TokenState::ACTIVE) {
        state = TokenState::FINISHED;
    }
}

TokenState Token::getState() const {
    return state;
}

int Token::getCell() const {
    return pos.getCell();
}

int Token::getSteps() const {
    return stepsTaken;
}

int Token::getId() const {
    return id;
}

int Token::getColour() const {
    return colour;
}

std::ostream& operator<<(std::ostream& out,const Token& token) {
    out << "T" << token.id << ": ";
    if (token.state == TokenState::HOME) {
        out << "HOME";
    } else if (token.state == TokenState::FINISHED) {
        out << "FINISHED";
    } else {
        out << token.pos<< " (steps " << token.stepsTaken << ")";
    }
    return out;
}
