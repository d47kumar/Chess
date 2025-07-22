#include "chessgame.h"
#include <iostream>
#include <cctype>
#include <algorithm>

// Constructor
ChessGame::ChessGame()
    : board(std::make_unique<Board>(false)),
      whitePlayer(nullptr),
      blackPlayer(nullptr),
      textDisplay(nullptr),
      // graphicalDisplay(nullptr),
      currentPlayer("WHITE"),
      gameState(GameState::NOT_STARTED),
      gameRunning(false),
      setupMode(false),
      whiteScore(0.0),
      blackScore(0.0) {}

// Destructor
ChessGame::~ChessGame() = default;

// Game control
bool ChessGame::startGame(const std::string& white, const std::string& black) {
    if (gameRunning) return false;
    std::cout << "Starting game with players: " << white << " (White) vs " << black << " (Black)" << std::endl;
    whitePlayer = createPlayer(white, "WHITE");
    blackPlayer = createPlayer(black, "BLACK");
    if (!whitePlayer || !blackPlayer) return false;
    std::cout << "Game started!" << std::endl;
    board = std::make_unique<Board>(false);
    currentPlayer = "WHITE";
    gameState = GameState::PLAYING;
    gameRunning = true;
    setupMode = false;
    moveHistory.clear();
    textDisplay->setBoard(board.get());
    if (textDisplay) textDisplay->notify();
    // if (graphicalDisplay) graphicalDisplay->notify();
    return true;
}

void ChessGame::endGame() {
    gameRunning = false;
    gameState = GameState::NOT_STARTED;
    whitePlayer.reset();
    blackPlayer.reset();
    moveHistory.clear();
}

bool ChessGame::isGameRunning() const {
    return gameRunning;
}

// Move handling
bool ChessGame::move(const std::string& from, const std::string& to, const std::string& promotion) {
    if (!gameRunning || setupMode) return false;
    std::cout << "Moving piece from " << from << " to " << to << std::endl;
    Position fromPos = parsePosition(from);
    Position toPos = parsePosition(to);
    if (!fromPos.isValid() || !toPos.isValid()) return false;
    Move move(fromPos, toPos);
    if (!promotion.empty()) {
        move.setIsPromotion(true);
        move.setPromotionPiece(promotion);
        std::cout << "Promotion to " << promotion << std::endl;
    }
    if (!isValidMove(move)) return false;
    if (!makeMove(move)) return false;
    moveHistory.push_back(move);
    updateGameState();
    switchPlayer();
    // if (graphicalDisplay) graphicalDisplay->notify();
    return true;
}

bool ChessGame::move() {
    if (!gameRunning || setupMode) return false;
    Player* player = (currentPlayer == "WHITE") ? whitePlayer.get() : blackPlayer.get();
    if (!player) return false;
    Move move = player->makeMove(board.get());
    if (!isValidMove(move)) return false;
    if (!makeMove(move)) return false;
    moveHistory.push_back(move);
    updateGameState();
    switchPlayer();
    // if (graphicalDisplay) graphicalDisplay->notify();
    return true;
}

void ChessGame::resign() {
    if (!gameRunning) return;
    gameState = GameState::RESIGNED;
    if (currentPlayer == "WHITE") {
        blackScore += 1.0;
        std::cout << "Black wins by resignation!" << std::endl;
    } else {
        whiteScore += 1.0;
        std::cout << "White wins by resignation!" << std::endl;
    }
    endGame();
}

// Setup mode
void ChessGame::enterSetupMode() {
    setupMode = true;
    gameRunning = false;
    board = std::make_unique<Board>(true);
    textDisplay->setBoard(board.get());
    if (textDisplay) textDisplay->notify();
    // if (graphicalDisplay) graphicalDisplay->notify();
}

void ChessGame::exitSetupMode() {
    setupMode = false;
    if (isValidSetup()) {
        gameRunning = true;
        gameState = GameState::PLAYING;
    }
}

bool ChessGame::addPiece(const std::string& piece, const std::string& position) {
    if (!setupMode) return false;
    if (piece.empty() || position.empty()) return false;
    char symbol = piece[0];
    Position pos = parsePosition(position);
    if (!pos.isValid()) return false;
    bool isWhite = std::isupper(symbol);
    std::string colour = isWhite ? "WHITE" : "BLACK";
    std::unique_ptr<Piece> newPiece = board->createPiece(symbol, pos, false);
    if (!newPiece) return false;
    board->setPiece(pos, std::move(newPiece));
    // if (graphicalDisplay) graphicalDisplay->notify();
    return true;
}

bool ChessGame::removePiece(const std::string& position) {
    if (!setupMode) return false;
    Position pos = parsePosition(position);
    if (!pos.isValid()) return false;
    board->removePiece(pos);
    // if (graphicalDisplay) graphicalDisplay->notify();
    return true;
}

void ChessGame::setTurn(const std::string& colour) {
    if (!setupMode) return;
    std::string col = colour;
    std::transform(col.begin(), col.end(), col.begin(), ::toupper);
    if (col == "WHITE" || col == "BLACK") {
        currentPlayer = col;
    }
}

// Display management
void ChessGame::attachDisplay(TextDisplay* display) {
    textDisplay.reset(display);
    textDisplay->setBoard(board.get());
}

void ChessGame::attachDisplay(GraphicalDisplay* display) {
    // graphicalDisplay.reset(display);
    // if (graphicalDisplay) graphicalDisplay->notify();
}

// Game state
GameState ChessGame::getGameState() const {
    return gameState;
}

std::string ChessGame::getCurrentPlayer() const {
    return currentPlayer;
}

void ChessGame::printFinalScores() const {
    std::cout << "Final Scores:" << std::endl;
    std::cout << "White: " << whiteScore << std::endl;
    std::cout << "Black: " << blackScore << std::endl;
}

// Private helper methods
std::unique_ptr<Player> ChessGame::createPlayer(const std::string& playerType, const std::string& colour) {
    if (playerType == "human") {
        return std::make_unique<HumanPlayer>(colour);
    }
    
    if (playerType == "computer[1]") {
        return std::make_unique<ComputerPlayer>(colour, 1);
    }

    if (playerType == "computer[2]") {
        return std::make_unique<ComputerPlayer>(colour, 2);
    }

    if (playerType == "computer[3]") {
        return std::make_unique<ComputerPlayer>(colour, 3);
    }

    if (playerType == "computer[4]") {
        return std::make_unique<ComputerPlayer>(colour, 4);
    }
    
    return nullptr;
}

Position ChessGame::parsePosition(const std::string& pos) const {
    if (pos.length() != 2) return Position(-1, -1);
    char file = std::tolower(pos[0]);
    char rank = pos[1];
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') return Position(-1, -1);
    int row = 8 - (rank - '0');
    int col = file - 'a';
    return Position(row, col);
}

bool ChessGame::isValidSetup() const {
    return board->isValidSetup();
}

void ChessGame::updateGameState() {
    if (board->isCheckmate(currentPlayer)) {
        gameState = GameState::CHECKMATE;
        if (currentPlayer == "WHITE") blackScore += 1.0;
        else whiteScore += 1.0;
        std::cout << (currentPlayer == "WHITE" ? "Black" : "White") << " wins by checkmate!" << std::endl;
        endGame();
    } else if (board->isStalemate(currentPlayer)) {
        gameState = GameState::STALEMATE;
        whiteScore += 0.5;
        blackScore += 0.5;
        std::cout << "Stalemate!" << std::endl;
        endGame();
    } else if (board->isInCheck(currentPlayer)) {
        gameState = GameState::CHECK;
        std::cout << currentPlayer << " is in check." << std::endl;
    } else {
        gameState = GameState::PLAYING;
    }
}

void ChessGame::switchPlayer() {
    currentPlayer = (currentPlayer == "WHITE") ? "BLACK" : "WHITE";
}

void ChessGame::updateScores() {
    // Already handled in updateGameState
}

bool ChessGame::isValidMove(const Move& move) const {
    Piece* piece = board->getPiece(move.getFrom());
    if (!piece || piece->getColour() != currentPlayer) return false;
    return board->isValidMove(move.getFrom(), move.getTo(), currentPlayer);
}

bool ChessGame::makeMove(const Move& move) {
    return board->makeMove(move);
}
