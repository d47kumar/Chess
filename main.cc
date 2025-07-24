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
            string from, to, promo;
            iss >> from >> to >> promo;
            if (!chessGame.isGameRunning()) {
                cout << "No active game. Use 'game' to start." << endl;
            } else {
                bool success = chessGame.move(from, to, promo);
                if (!success) cout << "Illegal move." << endl;
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
            cout << "Unknown command." << endl;
        }
    }

    chessGame.printFinalScores();
    return 0;
}
