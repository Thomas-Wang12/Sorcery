#include <iostream>
#include <fstream>
#include <sstream>
#include "Game.h"
#include "globals.h"

using namespace std;

void loadInitializationFile(const string& filename, const string& deck1File, const string& deck2File, Game& game) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open init file: " << filename << endl;
        return;
    }
    string playerName;
    getline(file, playerName);
    game.setPlayer1Name(playerName);

    getline(file, playerName);
    game.setPlayer2Name(playerName);

    game.loadPlayer1Deck(deck1File);
    game.loadPlayer2Deck(deck2File);

    string command;
    while (getline(file, command)) {
        game.processCommand(command);
    }
    file.close();
}

int main(int argc, char* argv[]) {
    std::string deck1File = "default.deck";
    std::string deck2File = "default.deck";
    std::string initFile;
    bool initSpecified = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-deck1" && i + 1 < argc) {
            deck1File = argv[++i];
        } else if (arg == "-deck2" && i + 1 < argc) {
            deck2File = argv[++i];
        } else if (arg == "-init" && i + 1 < argc) {
            initFile = argv[++i];
            initSpecified = true;
        } else if(arg == "-testing") {
            testing = true;

        }
    }

    Game game;

    if (initSpecified) {
        loadInitializationFile(initFile, deck1File, deck2File, game);
    } else {
        // Default player names
        game.setPlayer1Name("Player1");
        game.setPlayer2Name("Player2");
        game.loadPlayer1Deck(deck1File);
        game.loadPlayer2Deck(deck2File);
    }

    game.start();

    // Main game loop
    string input;
    while (true) {
        getline(cin, input);
        game.processCommand(input);
        if(input == "quit") {
            break;
        }
    }

    return 0;
}

