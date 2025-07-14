#ifndef POSITION_H
#define POSITION_H
#include <iostream>;

class Position {
    int row;
    int column;

    public:

        // Constructor
        Position(int row, int column, bool occupied);

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
