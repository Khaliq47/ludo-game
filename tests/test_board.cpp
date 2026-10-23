#include <iostream>
#include "board.hpp"
#include "player.hpp"
#include "token.hpp"
using namespace std;

static void check(bool ok, const char* msg) {
    cout << (ok ? "PASS: " : "FAIL: ") << msg << "\n";
}

int main() {
    Board board;

    // safe cells
    check(board.isSafe(0) && board.isSafe(8), "start and star cells are safe");
    check(!board.isSafe(5), "cell 5 is not safe");
    check(!board.isSafe(99) && !board.isSafe(-1), "out-of-range cells are not safe");
    check(board.getStartCell(YELLOW) == 26, "yellow starts at 26");
    check(board.getStartCell(7) == -1, "invalid colour gives -1");

    // cascading
    board.markSafe(5).markSafe(6);
    check(board.isSafe(5) && board.isSafe(6), "markSafe cascades");
    cout << board << "\n";

    // capture on a normal cell
    Player players[2] = { Player("A", RED), Player("B", YELLOW) };
    players[0][0].leaveHome();
    players[0][0].move(10);                  // red at cell 10
    players[1][0].leaveHome();
    players[1][0].move(36);                  // yellow: (26+36)%52 = 10
    int n = board.checkCapture(players[1][0], players, 2);
    check(n == 1, "yellow captures red on cell 10");
    check(players[0][0].getState() == TokenState::HOME, "captured token is back home");

    // no capture on a safe cell
    players[0][1].leaveHome();
    players[0][1].move(8);                   // red at cell 8 (safe)
    players[1][1].leaveHome();
    players[1][1].move(34);                  // yellow: (26+34)%52 = 8
    n = board.checkCapture(players[1][1], players, 2);
    check(n == 0, "no capture on safe cell");
    check(players[0][1].getState() == TokenState::ACTIVE, "token on safe cell survives");

    // own tokens are never captured
    players[0][2].leaveHome();
    players[0][2].move(20);
    players[0][3].leaveHome();
    players[0][3].move(20);
    n = board.checkCapture(players[0][3], players, 2);
    check(n == 0, "own colour is not captured");

    return 0;
}