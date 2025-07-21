#include "chessgame.h"
#include "humanplayer.h"
#include "player.h"
#include <iostream>

ChessGame::ChessGame()
    : currentPlayer(nullptr), board(nullptr), whitePlayer(nullptr), blackPlayer(nullptr), gameState(GameState::NotStarted) {}

ChessGame::~ChessGame() {
    delete board;
    delete whitePlayer;
    delete blackPlayer;
}

void ChessGame::startGame(const std::string& whiteType, const std::string& blackType) {
    // Clean up previous game if any
    delete board;
    delete whitePlayer;
    delete blackPlayer;
    board = new Board(false); // Not in setup mode
    board->setupStandardPosition();
    // For now, only human players are supported
    whitePlayer = new HumanPlayer("white");
    blackPlayer = new HumanPlayer("black");
    currentPlayer = whitePlayer;
    gameState = GameState::InProgress;
    moveHistory.clear();
}

bool ChessGame::makeMove(const Move& move) {
    if (gameState != GameState::InProgress) return false;
    if (!board->makeMove(move)) return false;
    moveHistory.push_back(move);
    // Switch player
    currentPlayer = (currentPlayer == whitePlayer) ? blackPlayer : whitePlayer;
    // Check for game end
    if (board->isCheckmate(currentPlayer->getColour())) {
        gameState = GameState::Checkmate;
    } else if (board->isStalemate(currentPlayer->getColour())) {
        gameState = GameState::Stalemate;
    }
    return true;
}

void ChessGame::resign() {
    if (gameState != GameState::InProgress) return;
    gameState = GameState::Resigned;
}

bool ChessGame::isGameOver() const {
    return gameState == GameState::Checkmate || gameState == GameState::Stalemate || gameState == GameState::Resigned;
}

ChessGame::GameState ChessGame::getGameState() const {
    return gameState;
}

Player* ChessGame::getCurrentPlayer() const {
    return currentPlayer;
}

Board* ChessGame::getBoard() const {
    return board;
}

const std::vector<Move>& ChessGame::getMoveHistory() const {
    return moveHistory;
}
