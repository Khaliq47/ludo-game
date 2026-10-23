#include "dice.hpp"
#include <cstdlib>  
using namespace std;



Dice::Dice() {
    sides = 6;
    lastRoll = 0;
}

Dice::Dice(int sides) {
    this->sides = (sides >= 2) ? sides : 6;  
    this->lastRoll = 0;
}

int Dice::roll() {
    lastRoll = rand() % sides + 1;
    return lastRoll;
}

int Dice::roll(int bonus) {
    lastRoll = rand() % sides + 1 + bonus;
    return lastRoll;
}

int Dice::getLastRoll() const {
    return lastRoll;
}

ostream& operator<<(ostream& out, const Dice& d) {
    out << "Dice: " << d.lastRoll;
    return out;
}
