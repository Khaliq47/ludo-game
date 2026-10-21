#include "board.hpp"
#include <iostream>

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