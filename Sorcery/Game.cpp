#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "globals.h"

using namespace std;

Game::Game() : player1("Player1"), player2("Player2"), turn(1) {}

void Game::start() {
    // Initialize the Game
    //cout << player1.deck.size() << endl << player2.deck.size() << endl;

    for (int i = 0; i < 5; ++i) {
        player1.drawCard();
        player2.drawCard();
    }
    player1.board = {nullptr, nullptr, nullptr, nullptr, nullptr};
    player2.board = {nullptr, nullptr, nullptr, nullptr, nullptr};

    cout << "Game started! " << player1.getName() << " vs " << player2.getName() << endl;
    cout << player1.getName() << "'s initial hand: " << endl;
    player1.showHand();
    cout << player2.getName() << "'s initial hand: " << endl;
    player2.showHand();

    cout << "It's " << player1.getName() << "'s turn." << endl;


}

void Game::endTurn() {
    if (turn % 2 == 1) {
        player1.endTurn();
        player2.startTurn();
    } else {
        player2.endTurn();
        player1.startTurn();
    }
    ++turn;
}

void Game::playCard(Player* player, Card* card) {
    //player->playCard(card);
}

void Game::loadPlayer1Deck(const string& filename) {
    player1.loadDeck(filename, cardDatabase);
}

void Game::loadPlayer2Deck(const string& filename) {
    player2.loadDeck(filename, cardDatabase);
}

void Game::setPlayer1Name(const string& name) {
    player1 = Player(name);
}

void Game::setPlayer2Name(const string& name) {
    player2 = Player(name);
}

void Game::processCommand(const string& command) {
    // Example command processing
    // "play 1" means current player plays the card at index 1 in their hand
    istringstream iss(command);
    string cmd;
    int index;
    iss >> cmd >> index;
    Player* currentPlayer;
    Player* opponentPlayer;
    if (turn % 2 == 1) {
        currentPlayer = &player1;
        opponentPlayer = &player2;
    } else {
        currentPlayer = &player2;
        opponentPlayer = &player1;
    }
    if (cmd == "play") {
        int targetPlayerIndex;
        int targetIndex;
        if (iss >> targetPlayerIndex) {
            if(iss >> targetIndex) {
                if (turn % 2 == 1) {
                    player1.playCard(index, targetPlayerIndex, targetIndex, opponentPlayer);
                } else {
                    player2.playCard(index, targetPlayerIndex, targetIndex, opponentPlayer);
                }
            } else {
                cout << "Can't use the play command like that." << endl;
            }
        } else {
            if (turn % 2 == 1) {
                player1.playCard(index, opponentPlayer);
            } else {
                player2.playCard(index, opponentPlayer);
            }
        }

    } else if (cmd == "end") {
        if (turn % 2 == 1) {
            cout << player1.getName() << " has ended the turn." << endl;
        } else {
            cout << player2.getName() << " has ended the turn." << endl;
        }
        endTurn();
    } else if (cmd == "help") {
        cout << "Commands: help -- Display this message." << endl <<
                "end -- End the current player’s turn." << endl <<
                "quit -- End the game." << endl <<
                "attack minion other-minion -- Orders minion to attack other-minion." << endl <<
                "attack minion -- Orders minion to attack the opponent." << endl <<
                "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl <<
                "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player." << endl <<
                "inspect minion -- View a minion’s card and all enchantments on that minion." << endl <<
                "hand -- Describe all cards in your hand." << endl <<
                "board -- Describe all cards on the board." << endl;

    } else if (cmd == "quit") {
        cout << "Quit" << endl;

    } else if (cmd == "draw") {
        if(testing) {
            if (turn % 2 == 1) {
                player1.drawCard();
            } else {
                player2.drawCard();
            }

        } else {
            cout << "Only available in Testing mode" << endl;
        }

    } else if (cmd == "discard") {
        if(testing) {
            if (turn % 2 == 1) {
                player1.discardCard(index);
            } else {
                player2.discardCard(index);
            }
        } else {
            cout << "Only available in Testing mode" << endl;
        }


    } else if (cmd == "attack") {
        int targetIndex;
        if (iss >> targetIndex) { // Two inputs: attackerIndex and targetIndex
            if (turn % 2 == 1) {
                player1.attack(index, targetIndex, player2);
            } else {
                player2.attack(index, targetIndex, player1);
            }
        } else { // One input: attackerIndex
            if (turn % 2 == 1) {
                player1.attackHero(index, player2);
            } else {
                player2.attackHero(index, player1);
            }
        }
    } else if (cmd == "use") {
        cout << "use" << endl;

    } else if (cmd == "describe") {
        cout << "describe" << endl;

    } else if (cmd == "hand") {
        if (turn % 2 == 1) {
            player1.showHand();
        } else {
            player2.showHand();
        }
    } else if (cmd == "board") {
        if (turn % 2 == 1) {
            player1.showBoard();
            player2.showBoard();
        } else {
            player2.showBoard();
            player1.showBoard();
        }

    }
}
