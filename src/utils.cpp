#include "Utils.h"
#include "Player.h"
#include <iostream>
#include <limits>
using namespace std;

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
            if (p[i].getState() == HOME && p.canMove(i, roll))
                return i;
    }

    
    int best = -1, bestSteps = -1;
    for (int i = 0; i < 4; i++) {
        if (p[i].getState() == ACTIVE && p.canMove(i, roll)
            && p[i].getSteps() > bestSteps) {
            best = i;
            bestSteps = p[i].getSteps();
        }
    }
    return best;
}
