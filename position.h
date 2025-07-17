#ifndef POSITION_H
#define POSITION_H
#include <iostream>
#include "board.h"
#include "piece.h"

class Position {
    int row;
    int column;

    public:

        // Constructor
        Position(int row, int column);

        // Methods
        bool isValid() const;

        // Getters
        int getRow() const;
        int getColumn() const;

        // Setters
        void setRow(int newRow);
        void setColumn(int newColumn);
};

#endif
