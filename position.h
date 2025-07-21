#ifndef POSITION_H
#define POSITION_H
#include <iostream>

class Position {
    int row;
    int column;

public:
    // Constructor
    Position(int row = -1, int column = -1);

    // Methods
    bool isValid() const;

    // Getters
    int getRow() const;
    int getColumn() const;

    // Setters
    void setRow(int newRow);
    void setColumn(int newColumn);

    // Operators for map usage
    bool operator<(const Position& other) const;
    bool operator==(const Position& other) const;
};

#endif
