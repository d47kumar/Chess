#include "board.h"

// Private Methods
bool Board::wouldBeInCheck(const std::string& colour, Move testMove) const {
    Board tempBoard = *this;
    
    std::unique_ptr<Piece> movingPiece = std::move(tempBoard.squares[testMove.getFrom()]);
    tempBoard.squares.erase(testMove.getFrom());
    
    if (movingPiece) {
        movingPiece->setPosition(testMove.getTo());
        
        if (dynamic_cast<King*>(movingPiece.get())) {
            tempBoard.updateKingPosition(colour, testMove.to);
        }
        
        tempBoard.squares[testMove.to] = std::move(movingPiece);
        
        return tempBoard.isInCheck(colour);
    }
    
    return true; 
} // Board::wouldBeInCheck

std::unique_ptr<Piece> Board::createPiece(char pieceSymbol, Position pos, bool hasMoved) const {
    std::string colour = (pieceSymbol >= 'A' && pieceSymbol <= 'Z') ? "WHITE" : "BLACK";
    char upperSymbol = std::toupper(pieceSymbol);

    if (upperSymbol == 'K') {
        return std::make_unique<King>(colour, pos, hasMoved);
    } else if (upperSymbol == 'Q') {
        return std::make_unique<Queen>(colour, pos, hasMoved);
    } else if (upperSymbol == 'R') {
        return std::make_unique<Rook>(colour, pos, hasMoved);
    } else if (upperSymbol == 'B') {
        return std::make_unique<Bishop>(colour, pos, hasMoved);
    } else if (upperSymbol == 'N') {
        return std::make_unique<Knight>(colour, pos, hasMoved);
    } else if (upperSymbol == 'P') {
        return std::make_unique<Pawn>(colour, pos, hasMoved);
    } else {
        return nullptr;
    }
} // Board::createPiece

// Public Methods
Move Board::getLastMove() const {
    return lastMove;
}

Board::Board(bool setup) : whiteKingPos(7, 4), blackKingPos(0, 4), setup{setup}, 
                           lastMove(Position(-1, -1), Position(-1, -1)) {
    if (!setup) {
        setupStandardPosition();
    }
} // Board::Board

Board::~Board() {} // Board::~Board

Piece* Board::getPiece(Position pos) const {
    auto it = squares.find(pos);
    return (it != squares.end()) ? it->second.get() : nullptr;
} // Board::getPiece

void Board::setPiece(Position pos, std::unique_ptr<Piece> piece) {
    if (piece) {
        piece->setPosition(pos);
        if (piece->getColour() == "WHITE" && dynamic_cast<King*>(piece.get())) {
            whiteKingPos = pos;
        } else if (piece->getColour() == "BLACK" && dynamic_cast<King*>(piece.get())) {
            blackKingPos = pos;
        }
    }
    squares[pos] = std::move(piece);
    notifyObservers();
} // Board::setPiece

void Board::removePiece(Position pos) {
    squares.erase(pos);
    notifyObservers();
} // Board::removePiece

bool Board::isValidMove(Position from, Position to, const std::string& colour) const {
    if (!from.isValid() || !to.isValid()) return false;
    
    Piece* piece = getPiece(from);
    if (!piece || piece->getColour() != colour) return false;
    
    if (!piece->isValidMove(to, const_cast<Board*>(this))) return false;
    
    if (dynamic_cast<Bishop*>(piece) || dynamic_cast<Rook*>(piece) || dynamic_cast<Queen*>(piece)) {
        if (!isPathClear(from, to)) return false;
    }
    
    Piece* destPiece = getPiece(to);
    if (destPiece && destPiece->getColour() == colour) return false;
    
    Move testMove(from, to);
    return !wouldBeInCheck(colour, testMove);
} // Board::isValidMove

bool Board::isPathClear(Position from, Position to) const {
    int rowDiff = to.getRow() - from.getRow();
    int colDiff = to.getColumn() - from.getColumn();
    
    if ((abs(rowDiff) == 2 && abs(colDiff) == 1) || 
        (abs(rowDiff) == 1 && abs(colDiff) == 2)) {
        return true;
    }
    
    int rowStep = (rowDiff == 0) ? 0 : (rowDiff > 0 ? 1 : -1);
    int colStep = (colDiff == 0) ? 0 : (colDiff > 0 ? 1 : -1);
    
    int currRow = from.getRow() + rowStep;
    int currCol = from.getColumn() + colStep;
    
    while (currRow != to.getRow() || currCol != to.getColumn()) {
        Position checkPos(currRow, currCol);
        if (getPiece(checkPos) != nullptr) return false;
        currRow += rowStep;
        currCol += colStep;
    }
    
    return true;
} // Board::isPathClear

bool Board::isSquareUnderAttack(Position pos, const std::string& attackingColour) const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Position checkPos(row, col);
            Piece* piece = getPiece(checkPos);
            
            if (piece && piece->getColour() == attackingColour) {
                if (dynamic_cast<Pawn*>(piece)) {
                    int direction = (attackingColour == "WHITE") ? -1 : 1;
                    int targetRow = pos.getRow();
                    int targetCol = pos.getColumn();
                    
                    if (targetRow == row + direction && 
                        abs(targetCol - col) == 1) {
                        return true;
                    }
                } else {
                    if (piece->isValidMove(pos, const_cast<Board*>(this))) {
                        if (dynamic_cast<Bishop*>(piece) || dynamic_cast<Rook*>(piece) || 
                            dynamic_cast<Queen*>(piece)) {
                            if (isPathClear(checkPos, pos)) {
                                return true;
                            }
                        } else {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
} // Board::isSquareUnderAttack

bool Board::isInCheck(const std::string& colour) const {
    Position kingPos = getKingPosition(colour);
    std::string enemyColour = (colour == "WHITE") ? "BLACK" : "WHITE";
    return isSquareUnderAttack(kingPos, enemyColour);
} // Board::isInCheck

bool Board::isCheckmate(const std::string& colour) const {
    if (!isInCheck(colour)) return false;
    
    std::vector<Move> legalMoves = getLegalMoves(colour);
    return legalMoves.empty();
} // Board::isCheckmate

bool Board::isStalemate(const std::string& colour) const {
    if (isInCheck(colour)) return false;
    
    std::vector<Move> legalMoves = getLegalMoves(colour);
    return legalMoves.empty();
} // Board::isStalemate

std::vector<Move> Board::getLegalMoves(const std::string& colour) const {
    std::vector<Move> legalMoves;
    
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Position from(row, col);
            Piece* piece = getPiece(from);
            
            if (piece && piece->getColour() == colour) {
                for (int targetRow = 0; targetRow < 8; ++targetRow) {
                    for (int targetCol = 0; targetCol < 8; ++targetCol) {
                        Position to(targetRow, targetCol);
                        
                        if (isValidMove(from, to, colour)) {
                            Move move(from, to);
                            
                            if (dynamic_cast<Pawn*>(piece)) {
                                if ((colour == "WHITE" && targetRow == 0) ||
                                    (colour == "BLACK" && targetRow == 7)) {
                                    legalMoves.emplace_back(from, to, true, "Q");
                                    legalMoves.emplace_back(from, to, true, "R");
                                    legalMoves.emplace_back(from, to, true, "B");
                                    legalMoves.emplace_back(from, to, true, "N");
                                    continue;
                                }
                                if (canEnPassant(from, to, lastMove)) {
                                    move.isEnPassant = true;
                                }
                            }
                            
                            if (dynamic_cast<King*>(piece) && abs(targetCol - col) == 2) {
                                Position rookPos;
                                if (targetCol > col) {
                                    rookPos = Position(row, 7); 
                                } else {
                                    rookPos = Position(row, 0); 
                                }
                                
                                if (canCastle(from, rookPos)) {
                                    move.isCastling = true;
                                }
                            }
                            legalMoves.push_back(move);
                        }
                    }
                }
            }
        }
    }
    
    return legalMoves;
} // Board::getLegalMoves

bool Board::canCastle(Position kingPos, Position rookPos) const {
    Piece* king = getPiece(kingPos);
    Piece* rook = getPiece(rookPos);
    
    if (!king || !rook) return false;
    if (king->getHasMoved() || rook->getHasMoved()) return false;
    if (!dynamic_cast<King*>(king) || !dynamic_cast<Rook*>(rook)) return false;
    if (king->getColour() != rook->getColour()) return false;
    
    if (isInCheck(king->getColour())) return false;
    
    if (!isPathClear(kingPos, rookPos)) return false;
    
    std::string enemyColour = (king->getColour() == "WHITE") ? "BLACK" : "WHITE";
    int direction = (rookPos.getColumn() > kingPos.getColumn()) ? 1 : -1;
    
    for (int i = 1; i <= 2; ++i) {
        Position testPos(kingPos.getRow(), kingPos.getColumn() + i * direction);
        if (isSquareUnderAttack(testPos, enemyColour)) {
            return false;
        }
    }
    
    return true;
} // Board::canCastle

bool Board::canEnPassant(Position from, Position to, Move lastMove) const {
    Piece* pawn = getPiece(from);
    if (!pawn || !dynamic_cast<Pawn*>(pawn)) return false;
    
    Piece* lastMovedPiece = getPiece(lastMove.to);
    if (!lastMovedPiece || !dynamic_cast<Pawn*>(lastMovedPiece)) return false;
    
    if (abs(lastMove.to.getColumn() - from.getColumn()) != 1) return false;
    if (lastMove.to.getRow() != from.getRow()) return false;
    if (lastMovedPiece->getColour() == pawn->getColour()) return false;
    
    if (abs(lastMove.to.getRow() - lastMove.from.getRow()) != 2) return false;
    
    int direction = (pawn->getColour() == "WHITE") ? -1 : 1;
    Position expectedTo(from.getRow() + direction, lastMove.to.getColumn());
    
    return to == expectedTo;
} // Board::canEnPassant

bool Board::makeMove(Move move) {
    Piece* piece = getPiece(move.from);
    if (!piece) return false;
    
    std::string colour = piece->getColour();
    
    if (!isValidMove(move.from, move.to, colour)) return false;

    if (!move.getIsEnPassant()) {
        if (dynamic_cast<Pawn*>(piece) && canEnPassant(move.from, move.to, lastMove)) {
            move.setIsEnPassant(true);
        }
    }
    
    if (!move.getIsCastling()) {
        if (dynamic_cast<King*>(piece) && abs(move.to.getColumn() - move.from.getColumn()) == 2) {
            Position rookPos = (move.to.getColumn() > move.from.getColumn())
                               ? Position(move.from.getRow(), 7)
                               : Position(move.from.getRow(), 0);
            if (canCastle(move.from, rookPos)) {
                move.setIsCastling(true); // tag it as castling
            }
        }
    }
    
    lastMove = move;
    
    if (move.isCastling) {
        std::unique_ptr<Piece> king = std::move(squares[move.from]);
        squares.erase(move.from);
        king->setPosition(move.to);
        king->setHasMoved(true);
        squares[move.to] = std::move(king);
        
        Position rookFrom, rookTo;
        if (move.to.getColumn() > move.from.getColumn()) {
            rookFrom = Position(move.from.getRow(), 7);
            rookTo = Position(move.from.getRow(), 5);
        } else {
            rookFrom = Position(move.from.getRow(), 0);
            rookTo = Position(move.from.getRow(), 3);
        }
        
        std::unique_ptr<Piece> rook = std::move(squares[rookFrom]);
        squares.erase(rookFrom);
        rook->setPosition(rookTo);
        rook->setHasMoved(true);
        squares[rookTo] = std::move(rook);
        
        updateKingPosition(colour, move.to);
    } else if (move.isEnPassant) {
        Position capturedPawnPos = lastMove.getTo();
        Position temp{capturedPawnPos.getRow() + 1, capturedPawnPos.getColumn()};
        squares.erase(temp);
        std::unique_ptr<Piece> pawn = std::move(squares[move.from]);
        squares.erase(move.from);
        pawn->setPosition(move.to);
        pawn->setHasMoved(true);
        squares[move.to] = std::move(pawn);
    } else {
        std::unique_ptr<Piece> movingPiece = std::move(squares[move.from]);
        squares.erase(move.from);
        
        if (move.isPromotion) {
            movingPiece = createPiece(move.promotionPiece[0], move.to, true);
        } else {
            movingPiece->setPosition(move.to);
            movingPiece->setHasMoved(true);
        }
        
        if (dynamic_cast<King*>(movingPiece.get())) {
            updateKingPosition(colour, move.to);
        }
        
        squares[move.to] = std::move(movingPiece);
    }
    notifyObservers();
    return true;


} // Board::makeMove

void Board::clearBoard() {
    squares.clear();
    whiteKingPos = Position(-1, -1);
    blackKingPos = Position(-1, -1);
    lastMove = Move(Position(-1, -1), Position(-1, -1));
    notifyObservers();
} // Board::clearBoard

void Board::setupStandardPosition() {
    squares.clear();
    
    squares[Position(0, 0)] = std::make_unique<Rook>("BLACK", Position(0, 0), false);
    squares[Position(0, 1)] = std::make_unique<Knight>("BLACK", Position(0, 1), false);
    squares[Position(0, 2)] = std::make_unique<Bishop>("BLACK", Position(0, 2), false);
    squares[Position(0, 3)] = std::make_unique<Queen>("BLACK", Position(0, 3), false);
    squares[Position(0, 4)] = std::make_unique<King>("BLACK", Position(0, 4), false);
    squares[Position(0, 5)] = std::make_unique<Bishop>("BLACK", Position(0, 5), false);
    squares[Position(0, 6)] = std::make_unique<Knight>("BLACK", Position(0, 6), false);
    squares[Position(0, 7)] = std::make_unique<Rook>("BLACK", Position(0, 7), false);
    
    for (int j = 0; j < 8; ++j) {
        squares[Position(1, j)] = std::make_unique<Pawn>("BLACK", Position(1, j), false);
    }
    
    // White pieces
    squares[Position(7, 0)] = std::make_unique<Rook>("WHITE", Position(7, 0), false);
    squares[Position(7, 1)] = std::make_unique<Knight>("WHITE", Position(7, 1), false);
    squares[Position(7, 2)] = std::make_unique<Bishop>("WHITE", Position(7, 2), false);
    squares[Position(7, 3)] = std::make_unique<Queen>("WHITE", Position(7, 3), false);
    squares[Position(7, 4)] = std::make_unique<King>("WHITE", Position(7, 4), false);
    squares[Position(7, 5)] = std::make_unique<Bishop>("WHITE", Position(7, 5), false);
    squares[Position(7, 6)] = std::make_unique<Knight>("WHITE", Position(7, 6), false);
    squares[Position(7, 7)] = std::make_unique<Rook>("WHITE", Position(7, 7), false);
    
    for (int j = 0; j < 8; ++j) {
        squares[Position(6, j)] = std::make_unique<Pawn>("WHITE", Position(6, j), false);
    }
    
    whiteKingPos = Position(7, 4);
    blackKingPos = Position(0, 4);
    notifyObservers();
} // Board::setupStandardPosition

bool Board::isValidSetup() const {
    int whiteKings = 0, blackKings = 0;
    
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Position pos(row, col);
            Piece* piece = getPiece(pos);
            
            if (piece) {
                if (dynamic_cast<King*>(piece)) {
                    if (piece->getColour() == "WHITE") whiteKings++;
                    else blackKings++;
                }
                
                if (dynamic_cast<Pawn*>(piece)) {
                    if (row == 0 || row == 7) return false;
                }
            }
        }
    }
    
    if (whiteKings != 1 || blackKings != 1) return false;
    
    if (isInCheck("WHITE") || isInCheck("BLACK")) return false;
    
    return true;
} // Board::isValidSetup

Position Board::getKingPosition(const std::string& colour) const {
    return (colour == "WHITE") ? whiteKingPos : blackKingPos;
} // Board::getKingPosition

void Board::updateKingPosition(const std::string& colour, Position newPos) {
    if (colour == "WHITE") {
        whiteKingPos = newPos;
    } else {
        blackKingPos = newPos;
    }
} // Board::updateKingPosition

std::ostream& operator<<(std::ostream& out, const Board& board) {
    out << std::endl;
    
    for (int row = 0; row < 8; ++row) {
        out << (8 - row) << " ";
        
        for (int col = 0; col < 8; ++col) {
            Position pos(row, col);
            Piece* piece = board.getPiece(pos);
            
            if (piece) {
                char symbol = '?';
                bool isWhite = (piece->getColour() == "WHITE");
                
                if (dynamic_cast<King*>(piece)) symbol = isWhite ? 'K' : 'k';
                else if (dynamic_cast<Queen*>(piece)) symbol = isWhite ? 'Q' : 'q';
                else if (dynamic_cast<Rook*>(piece)) symbol = isWhite ? 'R' : 'r';
                else if (dynamic_cast<Bishop*>(piece)) symbol = isWhite ? 'B' : 'b';
                else if (dynamic_cast<Knight*>(piece)) symbol = isWhite ? 'N' : 'n';
                else if (dynamic_cast<Pawn*>(piece)) symbol = isWhite ? 'P' : 'p';
                
                out << symbol;
            } else {
                out << ((row + col) % 2 == 0 ? ' ' : '_');
            }
        }
        out << std::endl;
    }
    
    out << "  abcdefgh" << std::endl;
    return out;
} // ostream& operator<<

// Copy constructor
Board::Board(const Board& other)
    : whiteKingPos(other.whiteKingPos),
      blackKingPos(other.blackKingPos),
      setup(other.setup),
      lastMove(other.lastMove)
{
    for (const auto& [pos, piecePtr] : other.squares) {
        if (piecePtr) {
            squares[pos] = piecePtr->clone();
        }
    }
}

// Copy assignment operator
Board& Board::operator=(const Board& other) {
    if (this == &other) return *this;
    whiteKingPos = other.whiteKingPos;
    blackKingPos = other.blackKingPos;
    setup = other.setup;
    lastMove = other.lastMove;
    squares.clear();
    for (const auto& [pos, piecePtr] : other.squares) {
        if (piecePtr) {
            squares[pos] = piecePtr->clone();
        }
    }
    return *this;
}
