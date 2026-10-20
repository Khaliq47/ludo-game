#ifndef POSITION_HPP
#define POSITION_HPP

#include <iostream>

class Position {
private:
    int cell;
    bool homeColumn;

public:
    Position();
    explicit Position(int cell, bool homeColumn = false);

    int getCell() const;
    void setCell(int cell);

    bool isInHomeColumn() const;
    void setHomeColumn(bool value);

    Position operator+(int steps) const;
    bool operator==(const Position& other) const;

    friend std::ostream& operator<<(std::ostream& out,const Position& position);
};

#endif
