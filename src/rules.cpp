#include "rules.hpp"
#include "token.hpp"

bool isValidRoll(int dice) {
    return dice >= 1 && dice <= 6;
}

bool canLeaveHome(int dice) {
    return dice == 6;
}

bool grantsExtraTurn(int dice) {
    return dice == 6;
}

bool tokenCanMove(const Token& token, int dice) {
    switch (token.getState()) {
        case TokenState::HOME:
            return canLeaveHome(dice);
        case TokenState::ACTIVE:
            return token.getSteps() + dice <= FINISH_STEP;   
        default:
            return false;                                
    }
}

bool reachesHomeExactly(const Token& token, int dice) {
    return token.getState() == TokenState::ACTIVE
        && token.getSteps() + dice == FINISH_STEP;
}

bool checkDice(DiceRule rule, int dice) {
    return rule(dice);
}