#include "king.h";

King::King(const std::string colour, Position pos, bool hasMoved) : Piece{colour, pos, hasMoved} {}; // King::King

bool King::isValidMove(Position movePosition) const {
    if (!movePosition.isValid()) { return false; }
    int row = getPosition().getRow();
    int column = getPosition().getColumn();
    int newRow = movePosition.getRow();
    int newColumn = movePosition.getColumn();

    int rowDiff = abs(newRow - row);
    int columnDiff = abs(newColumn - column);

    if (rowDiff == 0) { return ((columnDiff == 0) || (columnDiff == 1)); }
    if (columnDiff == 0) { return ((rowDiff == 0) || (columnDiff == 1)); }

    return false;

} // King::isValidMove

bool isCheckRow(int r, int c) {

} // King::isCheckRow

bool isCheckColumn(int r, int c) {

} // King::isCheckColumn

bool isCheckDiagonal(int r, int c) {

} // King::isCheckDiagonal

bool isCheckKnight(int r, int c) {
    
} // King::isCheckKnight

bool King::isCheck() {
    return isCheck(getPosition());
} // King::isCheck

bool isCheck(Position pos) {
    int r = pos.getRow();
    int c = pos.getColumn();

    return isCheckRow(r, c) || isCheckColumn(r, c) || isCheckKnight(r, c) || isCheckDiagonal(r, c);
} // King::isCheck

bool King::isKingCheckmate() {} // King::isCheckmate

bool King::isKingStalemate() {} // King::isStalemate
