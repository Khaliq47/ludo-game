#include "Player.h"
using namespace std;

static const char* COLOUR_NAMES[4] = { "RED", "GREEN", "YELLOW", "BLUE" };

Player::Player() {
    name = "";
    colour = 0;
    finishedCount = 0;
    chooser = 0;
    for (int i = 0; i < 4; i++)
        tokens[i] = Token(i + 1, colour);
}

Player::Player(string name, int colour) {
    this->name = name;
    this->colour = colour;
    this->finishedCount = 0;
    this->chooser = 0;
    for (int i = 0; i < 4; i++)
        tokens[i] = Token(i + 1, colour);   
}

Player::~Player() {
    if (!name.empty())
        cout << "[Player " << name << " destroyed]\n";
}

Player& Player::setChooser(int (*f)(Player&, int)) {
    this->chooser = f;
    return *this;
}

Player& Player::setName(string name) {
    this->name = name;
    return *this;
}

Token& Player::operator[](int i) {
    if (i < 0 || i > 3) {
        cout << "Invalid token index " << i << ", using token 0.\n";
        return tokens[0];
    }
    return tokens[i];
}

const Token& Player::operator[](int i) const {
    if (i < 0 || i > 3) return tokens[0];
    return tokens[i];
}

bool Player::hasWon() const {
    return finishedCount == 4;
}

void Player::tokenFinished() {
    if (finishedCount < 4) finishedCount++;
}

bool Player::canMove(int index, int roll) const {
    if (index < 0 || index > 3) return false;
    const Token& t = tokens[index];
    switch (t.getState()) {
        case HOME:     return roll == 6;                              
        case ACTIVE:   return t.getSteps() + roll <= TOTAL_STEPS;     
        default:       return false;                                  
    }
}

bool Player::canMoveAny(int roll) const {
    for (int i = 0; i < 4; i++)
        if (canMove(i, roll)) return true;
    return false;
}

int Player::chooseToken(int roll) {
    if (chooser == 0) return -1;
    return chooser(*this, roll);
}

string Player::getName() const { return name; }
int Player::getColour() const { return colour; }
int Player::getFinishedCount() const { return finishedCount; }

string Player::getColourName() const {
    return COLOUR_NAMES[colour % 4];
}

ostream& operator<<(ostream& out, const Player& p) {
    out << p.getColourName() << " (" << p.name << ")\n";
    for (int i = 0; i < 4; i++)
        out << "  " << p.tokens[i] << "\n";     
    return out;
}
