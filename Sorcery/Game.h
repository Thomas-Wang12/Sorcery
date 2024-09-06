#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "CardDatabase.h"
#include <string>

using namespace std;

class Game {
private:
    Player player1;
    Player player2;
    int turn;
    CardDatabase cardDatabase;

public:
    Game();
    void start();
    void endTurn();
    void playCard(Player* player, Card* card);
    void loadPlayer1Deck(const string& filename);
    void loadPlayer2Deck(const string& filename);
    void setPlayer1Name(const string& name);
    void setPlayer2Name(const string& name);
    void processCommand(const string& command);
};

#endif // GAME_H
