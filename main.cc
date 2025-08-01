#include <iostream>
#include <sstream>
#include <memory>
#include "chessgame.h"
#include "textdisplay.h"
#include "graphicaldisplay.h"

using namespace std;

int main() {
    ChessGame chessGame;

    unique_ptr<TextDisplay> textDisplay = make_unique<TextDisplay>();
    chessGame.attachDisplay(textDisplay.get());

    unique_ptr<GraphicalDisplay> graphicsDisplay = make_unique<GraphicalDisplay>();
    chessGame.attachDisplay(graphicsDisplay.get());


    string input;
    bool running = true;

    while (running && cin) {
        cout << "chess> ";
        if (!(getline(cin, input))) break;

        istringstream iss{input};
        string command;
        iss >> command;

        if (command == "game") {
            string white, black;
            iss >> white >> black;
            if (!chessGame.startGame(white, black)) {
                cout << "Invalid player specification." << endl;
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
                        if (!success) std::cout << "Illegal move." << std::endl;
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
            cout << "Unknown command." << endl;
        }
    }

    chessGame.printFinalScores();
    return 0;
}
