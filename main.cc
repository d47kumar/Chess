#include <iostream>
#include <sstream>
#include <memory>
#include "chessgame.h"
#include "textdisplay.h"
#include "graphicaldisplay.h"

using namespace std;

int main() {
    ChessGame chessGame;

    std::unique_ptr<TextDisplay> textDisplay = std::make_unique<TextDisplay>();
    chessGame.attachDisplay(textDisplay.get());

    // std::unique_ptr<GraphicalDisplay> graphicsDisplay = std::make_unique<GraphicalDisplay>();
    // chessGame.attachDisplay(graphicsDisplay.get());

    std::string input;
    bool running = true;

    while (running && std::cin) {
        std::cout << "chess> ";
        if (!(std::getline(std::cin, input))) break;

        std::istringstream iss{input};
        std::string command;
        iss >> command;

        if (command == "game") {
            std::string white, black;
            iss >> white >> black;
            if (!chessGame.startGame(white, black)) {
                std::cout << "Invalid player specification." << std::endl;
            }
        }

        else if (command == "move") {
            if (!chessGame.isGameRunning()) {
                std::cout << "No active game. Use 'game' to start." << std::endl;
            } else {
                std::string currentPlayer = chessGame.getCurrentPlayer();
                Player* player = nullptr;
                if (currentPlayer == "WHITE") {
                    player = chessGame.getWhitePlayer();
                } else {
                    player = chessGame.getBlackPlayer();
                }

                std::string from, to, promo;
                iss >> from >> to >> promo;

                if (player && !player->isHuman()) {
                    if (!from.empty()) {
                        std::cout << "Just type 'move' for computer's turn." << std::endl;
                    } else {
                        bool success = chessGame.move();
                        if (!success) std::cout << "Illegal move." << std::endl;
                    }
                } else {
                    if (from.empty() || to.empty()) {
                        std::cout << "Usage: move <from> <to> [promotion]" << std::endl;
                    } else {
                        bool success = chessGame.move(from, to, promo);
                    }
                }
            }
        }

        else if (command == "resign") {
            chessGame.resign();
        }

        else if (command == "setup") {
            if (chessGame.isGameRunning()) {
                std::cout << "Cannot enter setup mode during a game." << std::endl;
                continue;
            }
            chessGame.enterSetupMode();
            std::string setupInput;
            while (true) {
                std::cout << "setup> ";
                if (!std::getline(std::cin, setupInput)) break;
                std::istringstream setupIss{setupInput};
                std::string setupCmd;
                setupIss >> setupCmd;
                if (setupCmd == "+") {
                    std::string piece, pos;
                    setupIss >> piece >> pos;
                    if (!chessGame.addPiece(piece, pos)) {
                        std::cout << "Invalid piece or position." << std::endl;
                    }
                    if (chessGame.isGameRunning()) break;
                } else if (setupCmd == "-") {
                    std::string pos;
                    setupIss >> pos;
                    if (!chessGame.removePiece(pos)) {
                        std::cout << "Invalid position or no piece to remove." << std::endl;
                    }
                } else if (setupCmd == "=") {
                    std::string colour;
                    setupIss >> colour;
                    if (colour != "white" && colour != "black") {
                        std::cout << "Invalid colour. Use 'white' or 'black'." << std::endl;
                        continue;
                    }
                    if (colour == "white") {
                        chessGame.setTurn("WHITE");
                    } else {
                        chessGame.setTurn("BLACK");
                    }
                } else if (setupCmd == "done") {
                    if (chessGame.isValidSetup()) {
                        chessGame.exitSetupMode();
                        std::cout << "Setup complete." << std::endl;
                        break;
                    } else {
                        std::cout << "Invalid setup: must have exactly one white king, one black king, no pawns on first/last row, and no king in check." << std::endl;
                    }
                } else {
                    std::cout << "Unknown setup command." << std::endl;
                }
            }
        }

        else if (command == "quit" || command == "exit") {
            running = false;
        }

        else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    chessGame.printFinalScores();
    return 0;
}
