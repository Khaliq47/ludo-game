#ifndef DICE_H
#define DICE_H

#include <iostream>

class Dice {
private:
    int sides;      
    int lastRoll;

public:
    Dice();                 
    Dice(int sides);        
    int roll();             
    int roll(int bonus);    
    int getLastRoll() const;

    friend std::ostream& operator<<(std::ostream& out, const Dice& d);
};

#endif
