#ifndef RULES_HPP
#define RULES_HPP

#include "types.hpp"

class Token;

typedef bool (*DiceRule)(int dice);
typedef bool (*TokenRule)(const Token& token, int dice);

bool isValidRoll(int dice);
bool canLeaveHome(int dice);
bool grantsExtraTurn(int dice);

bool tokenCanMove(const Token& token, int dice);   // renamed from canMove
bool reachesHomeExactly(const Token& token, int dice);

bool checkDice(DiceRule rule, int dice);

#endif