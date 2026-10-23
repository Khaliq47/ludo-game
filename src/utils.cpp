#include "utils.hpp"
#include "player.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

int readInt(const string& prompt, int low, int high) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= low && value <= high) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a number from " << low << " to " << high << ".\n";
    }
}

int humanChoice(Player& p, int roll) {
    if (!p.canMoveAny(roll)) return -1;
    int choice;
    while (true) {
        cout << p.getName() << ", move which token (1-4)? ";
        if (!(cin >> choice)) {
            if (cin.eof()) return -1;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number from 1 to 4.\n";
            continue;
        }
        if (choice < 1 || choice > 4) {
            cout << "Token number must be between 1 and 4.\n";
            continue;
        }
        if (!p.canMove(choice - 1, roll)) {
            cout << "Token " << choice << " cannot move with this roll. Pick another.\n";
            continue;
        }
        return choice - 1;
    }
}

int botChoice(Player& p, int roll) {
    if (!p.canMoveAny(roll)) return -1;
    if (roll == 6) {
        for (int i = 0; i < 4; i++)
            if (p[i].getState() == TokenState::HOME && p.canMove(i, roll)) return i;
    }
    int best = -1, bestSteps = -1;
    for (int i = 0; i < 4; i++) {
        if (p[i].getState() == TokenState::ACTIVE && p.canMove(i, roll)
            && p[i].getSteps() > bestSteps) {
            best = i;
            bestSteps = p[i].getSteps();
        }
    }
    return best;
}