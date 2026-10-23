#include "board.hpp"
#include "token.hpp"
#include "player.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

Board::Board() {
    // 1. nothing is safe at first
    for (int i = 0; i < TRACK_LENGTH; i++) {
        safeCell[i] = false;
    }

    // 2. start cell of each colour
    startCells[RED] = 0;
    startCells[GREEN] = 13;
    startCells[YELLOW] = 26;
    startCells[BLUE] = 39;

    // 3. start cells + 4 star cells are safe (cascaded calls)
    markSafe(0).markSafe(13).markSafe(26).markSafe(39)
               .markSafe(8).markSafe(21).markSafe(34).markSafe(47);

    cout << "[Board created]\n";
}

Board::~Board() {
    cout << "[Board destroyed]\n";
}

Board& Board::markSafe(int cell) {
    if (cell >= 0 && cell < TRACK_LENGTH) {
        this->safeCell[cell] = true;
    }
    return *this;
}

bool Board::isSafe(int cell) const {
    if (cell < 0 || cell >= TRACK_LENGTH) {
        return false;
    }
    return safeCell[cell];
}

int Board::getStartCell(int colour) const {
    if (colour < 0 || colour > 3) {
        return -1;
    }
    return startCells[colour];
}

string Board::cellText(int cell, const Player players[], int numPlayers) const {
    string s;
    for (int p = 0; p < numPlayers; p++) {
        for (int t = 0; t < TOKENS_PER_PLAYER; t++) {
            const Token& tk = players[p][t];
            if (tk.getState() == TokenState::ACTIVE && !tk.isInHomeColumn()
                && tk.getCell() == cell) {
                s += players[p].getColourName().substr(0, 1);
                s += to_string(t + 1);
                s += " ";
            }
        }
    }
    if (s.empty()) return isSafe(cell) ? "*" : ".";
    if (isSafe(cell)) s += "*";
    return s;
}

void Board::drawTrack(const Player players[], int numPlayers) const {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 13; col++) {
            int cell = row * 13 + col;
            cout << setw(2) << cell << ":" << left << setw(6)
                 << cellText(cell, players, numPlayers) << right;
        }
        cout << "\n";
    }
}

int Board::checkCapture(const Token& mover, Player players[], int numPlayers) const {
    if (mover.getState() != TokenState::ACTIVE || mover.isInHomeColumn()) return 0;

    int cell = mover.getCell();
    if (isSafe(cell)) return 0;                    

    int captured = 0;
    for (int p = 0; p < numPlayers; p++) {
        if (players[p].getColour() == mover.getColour()) continue;  
        for (int t = 0; t < TOKENS_PER_PLAYER; t++) {
            Token& other = players[p][t];
            if (other.getState() == TokenState::ACTIVE && !other.isInHomeColumn()
                && other.getCell() == cell) {
                cout << "Token " << mover.getId() << " captures "
                     << players[p].getColourName() << " token " << other.getId()
                     << " at cell " << cell << "!\n";
                other.sendHome();
                captured++;
            }
        }
    }
    return captured;
}

void Board::display() const {                
    display(nullptr, 0);
}

void Board::display(const Player& player) const {   
    display(&player, 1);
}

void Board::display(const Player players[], int numPlayers) const {
    cout << "\n=========== BOARD (* = safe) ===========\n";
    drawTrack(players, numPlayers);
    for (int i = 0; i < numPlayers; i++) {
        cout << players[i].getColourName() << ": ";
        for (int t = 0; t < TOKENS_PER_PLAYER; t++) {
            const Token& tk = players[i][t];
            if (tk.getState() == TokenState::HOME) cout << "T" << t + 1 << "[HOME] ";
            else if (tk.getState() == TokenState::FINISHED) cout << "T" << t + 1 << "[DONE] ";
            else if (tk.isInHomeColumn()) cout << "T" << t + 1 << "[col " << tk.getCell() << "] ";
            else cout << "T" << t + 1 << "[" << tk.getCell() << "] ";
        }
        cout << "\n";
    }
}

ostream& operator<<(ostream& out, const Board& board) {
    out << "Board safe cells:";
    for (int i = 0; i < TRACK_LENGTH; i++)
        if (board.safeCell[i]) out << " " << i;
    return out;
}