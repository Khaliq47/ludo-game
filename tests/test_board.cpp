#include <iostream>
#include "board.hpp"
using namespace std;

int main() {
    Board board;

    cout << "isSafe(0)  = " << board.isSafe(0)  << "  (expect 1)\n";
    cout << "isSafe(8)  = " << board.isSafe(8)  << "  (expect 1)\n";
    cout << "isSafe(5)  = " << board.isSafe(5)  << "  (expect 0)\n";
    cout << "isSafe(99) = " << board.isSafe(99) << "  (expect 0)\n";
    cout << "start of YELLOW = " << board.getStartCell(YELLOW) << "  (expect 26)\n";

    board.markSafe(5);
    cout << "after markSafe(5), isSafe(5) = " << board.isSafe(5) << "  (expect 1)\n";
    return 0;
}