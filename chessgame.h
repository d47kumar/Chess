#ifndef CHESSGAME_H
#define CHESSGAME_H

#include "player.h"
#include "board.h"
#include "move.h"
#include <vector>
#include <memory>
#include <string>

class ChessGame {
public:
    enum class GameState {
        NotStarted,
        InProgress,
        Checkmate,
        Stalemate,
        Resigned
    };

private:
    Player* currentPlayer;
    Board* board;
    Player* whitePlayer;
    Player* blackPlayer;
    GameState gameState;
    std::vector<Move> moveHistory;

public:
    ChessGame();
    ~ChessGame();

    void startGame(const std::string& whiteType, const std::string& blackType);
    bool makeMove(const Move& move);
    void resign();
    bool isGameOver() const;
    GameState getGameState() const;
    Player* getCurrentPlayer() const;
    Board* getBoard() const;
    const std::vector<Move>& getMoveHistory() const;
};

#endif
