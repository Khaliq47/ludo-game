#include <iostream>
#include "Position.hpp" 

Position::Position(): cell(-1), homeColumn(false) {}

Position::Position(int cell, bool homeColumn): cell(cell), homeColumn(homeColumn) {}

int Position::getCell() const {
    return cell;
}

void Position::setCell(int cell) {
    this->cell = cell;
}

bool Position::isInHomeColumn() const {
    return homeColumn;
}

void Position::setHomeColumn(bool value) {
    homeColumn = value;
}

Position Position::operator+(int steps) const {
    // Home-column movement is not circular.
    if (homeColumn) {
        return Position(cell + steps, true);
    }

    // Wrap around the 52-cell main track.
    int newCell = (cell + steps) % 52;

    // Handle negative steps safely too.
    if (newCell < 0) {
        newCell += 52;
    }

    return Position(newCell, false);
}

bool Position::operator==(const Position& other) const {
    return cell == other.cell && homeColumn == other.homeColumn;
}

std::ostream& operator<<(std::ostream& out,const Position& position) {
    if (position.homeColumn) {
        out << "Home column: " << position.cell;
    } else if (position.cell == -1) {
        out << "Position: HOME";
    } else {
        out << "Cell: " << position.cell;
    }

    return out;
}
