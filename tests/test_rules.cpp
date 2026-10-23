#include <iostream>
#include "rules.hpp"
#include "token.hpp"
using namespace std;

static void check(bool ok, const char* msg) {
    cout << (ok ? "PASS: " : "FAIL: ") << msg << "\n";
}

int main() {

    check(isValidRoll(1) && isValidRoll(6) && !isValidRoll(0) && !isValidRoll(7), "isValidRoll");
    check(canLeaveHome(6) && !canLeaveHome(5), "only a 6 leaves home");
    check(grantsExtraTurn(6) && !grantsExtraTurn(2), "only a 6 gives an extra turn");

    check(checkDice(isValidRoll, 4), "checkDice with isValidRoll");
    check(!checkDice(canLeaveHome, 4), "checkDice with canLeaveHome");
    TokenRule rule = tokenCanMove;
    DiceRule dr = grantsExtraTurn;
    check(dr(6), "DiceRule pointer works");

    Token t(1, 0);                     
    check(!tokenCanMove(t, 4) && tokenCanMove(t, 6), "token in yard needs a 6");
    check(rule(t, 6), "TokenRule pointer works");

    t.leaveHome();
    t.move(54);                       
    check(tokenCanMove(t, 3) && !tokenCanMove(t, 4), "exact roll needed to finish");
    check(reachesHomeExactly(t, 3) && !reachesHomeExactly(t, 2), "reachesHomeExactly");

    t.move(3);
    t.finish();                         
    check(!tokenCanMove(t, 1), "finished token cannot move");
    return 0;
}