#ifndef CHESSGAME_H
#define CHESSGAME_H
#include <memory>
#include <string>
#include "board.h"
#include "player.h"
#include "humanplayer.h"
#include "computerplayer.h"
#include "textdisplay.h"
#include "graphicaldisplay.h"
#include "move.h"

enum class GameState {
    NOT_STARTED,
    PLAYING,
    CHECK,
    CHECKMATE,
    STALEMATE,
    RESIGNED
};

class ChessGame {
    std::unique_ptr<Board> board;
    std::unique_ptr<Player> whitePlayer;
    std::unique_ptr<Player> blackPlayer;
    std::unique_ptr<TextDisplay> textDisplay;
    std::unique_ptr<GraphicalDisplay> graphicalDisplay;
    
    std::string currentPlayer;
    GameState gameState;
    bool gameRunning;
    bool setupMode;
    
    // Scoring
    double whiteScore;
    double blackScore;
    
    // Game history
    std::vector<Move> moveHistory;
    
public:
    ChessGame();
    ~ChessGame();
    
    // Game control
    bool startGame(const std::string& white, const std::string& black);
    void endGame();
    bool isGameRunning() const;
    
    // Move handling
    bool move(const std::string& from, const std::string& to, const std::string& promotion = "");
    bool move(); // For computer players
    void resign();
    
    // Setup mode
    void enterSetupMode();
    void exitSetupMode();
    bool addPiece(const std::string& piece, const std::string& position);
    bool removePiece(const std::string& position);
    void setTurn(const std::string& colour);
    
    // Display management
    void attachDisplay(TextDisplay* display);
    void attachDisplay(GraphicalDisplay* display);
    
    // Game state
    GameState getGameState() const;
    std::string getCurrentPlayer() const;
    void printFinalScores() const;
    
private:
    // Helper methods
    std::unique_ptr<Player> createPlayer(const std::string& playerType, const std::string& colour);
    Position parsePosition(const std::string& pos) const;
    bool isValidSetup() const;
    void updateGameState();
    void switchPlayer();
    
    // Move validation
    bool isValidMove(const Move& move) const;
    bool makeMove(const Move& move);
};

#endif
