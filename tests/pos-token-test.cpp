//move this file to the root of the folder then run:
//g++ -std=c++17 -Wall -Wextra -Iinclude main_file.cpp src/position.cpp src/token.cpp -o test_game.exe
//then run the exe file for the tests.
#include <iostream>
#include "position.hpp"
#include "token.hpp"
using namespace std;

int main() {
    cout << "========== POSITION TESTS ==========\n";

    Position p1(10);
    Position p2(10);
    Position p3(20);

    cout << "p1: " << p1 << '\n';
    cout << "p3: " << p3 << '\n';

    cout << "p1 == p2: " << (p1 == p2) << '\n'; // 1
    cout << "p1 == p3: " << (p1 == p3) << '\n'; // 0

    Position p4 = p1 + 5;
    cout << "p1 + 5: " << p4 << '\n'; // Cell: 15

    Position p5(50);
    cout << "p5 + 5: " << (p5 + 5) << '\n'; // Cell: 3

    p1.setCell(30);
    cout << "After setCell(30): " << p1 << '\n';
    cout << "getCell(): " << p1.getCell() << '\n';

    Position homeLane(2, true);
    cout << "Home-lane position: " << homeLane << '\n';
    cout << "isInHomeColumn(): " << homeLane.isInHomeColumn() << '\n';
    cout << "Home lane + 2: " << (homeLane + 2) << '\n';

    cout << "\n========== TOKEN TESTS ==========\n";

    Token t1(1, 0);
    cout << "New token: " << t1 << '\n';
    cout << "Initial state is HOME: "
         << (t1.getState() == TokenState::HOME) << '\n';

    t1.leaveHome();
    cout << "After leaveHome(): " << t1 << '\n';
    cout << "Cell: " << t1.getCell() << '\n';
    cout << "Steps: " << t1.getSteps() << '\n';

    t1.move(5);
    cout << "After move(5): " << t1 << '\n';
    cout << "Cell should be 5: " << t1.getCell() << '\n';
    cout << "Steps should be 5: " << t1.getSteps() << '\n';

    ++t1;
    cout << "After prefix ++: " << t1 << '\n';
    cout << "Cell should be 6: " << t1.getCell() << '\n';

    t1.move(45);
    cout << "After 51 steps total: " << t1 << '\n';
    cout << "Cell should be 51: " << t1.getCell() << '\n';

    t1.move(1);
    cout << "After 52 steps total: " << t1 << '\n';
    cout << "Should be in home column: " << t1.isInHomeColumn() << '\n';

    // Wrap-around test using GREEN (starts at 13)
    Token g(1, 1);
    g.leaveHome();
    g.move(40);
    cout << "Green after 40 steps, cell should be 1: " << g.getCell() << '\n';

    t1.sendHome();
    cout << "After sendHome(): " << t1 << '\n';
    cout << "State is HOME: "
         << (t1.getState() == TokenState::HOME) << '\n';

    t1.leaveHome();
    t1.finish();
    cout << "After leaveHome() and finish(): " << t1 << '\n';
    cout << "State is FINISHED: "
         << (t1.getState() == TokenState::FINISHED) << '\n';

    cout << "\n========== INVALID MOVEMENT TEST ==========\n";

    Token t2(2, 1);
    t2.move(5); // Should do nothing while token is HOME
    cout << "HOME token after move(5): " << t2 << '\n';
    cout << "Steps should remain 0: " << t2.getSteps() << '\n';

    cout << "\n========== TESTS COMPLETED ==========\n";

    return 0;
}