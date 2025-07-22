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
            std::string from, to, promo;
            iss >> from >> to >> promo;
            if (!chessGame.isGameRunning()) {
                std::cout << "No active game. Use 'game' to start." << std::endl;
            } else {
                bool success = chessGame.move(from, to, promo);
                if (!success) std::cout << "Illegal move." << std::endl;
            }
        }

        else if (command == "resign") {
            chessGame.resign();
        }

        else if (command == "setup") {
            chessGame.enterSetupMode();
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
