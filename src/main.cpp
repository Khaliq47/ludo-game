#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.hpp"
#include "utils.hpp"
using namespace std;

bool running = true;

void startGame2() {
    Game g(2);
    g.setup();
    g.run();
}

void startGame4() {
    Game g(4);
    g.setup();
    g.run();
}

void showRules() {
    cout << "\nRULES" << endl;
    cout << "- 4 tokens each, all start at home" << endl;
    cout << "- a 6 brings a token out, and gives another roll" << endl;
    cout << "- tokens go clockwise round 52 cells, then up their home column" << endl;
    cout << "- landing on an opponent sends it home, unless the cell is safe (*)" << endl;
    cout << "- you need the exact number to finish" << endl;
    cout << "- first player with all 4 tokens home wins" << endl;
}

void exitGame() {
    cout << "Bye!" << endl;
    running = false;
}

int main() {
    srand(time(0));

    void (*menu[4])() = { startGame2, startGame4, showRules, exitGame };

    while (running) {
        cout << "\n1. 2 player game" << endl;
        cout << "2. 4 player game" << endl;
        cout << "3. Rules" << endl;
        cout << "4. Exit" << endl;
        int choice = readInt("Choice: ", 1, 4);
        menu[choice - 1]();
    }
    return 0;
}
