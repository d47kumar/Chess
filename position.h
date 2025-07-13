#ifndef POSITION_H
#define POSITION_H
#include <iostream>;

class Position {
    int row;
    int column;

    public:
        bool isValid() const;

        // Getters
        int getRow() const;
        int getColumn() const;
};

#endif
