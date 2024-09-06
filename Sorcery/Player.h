#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Card.h"
#include "Minion.h"
#include "CardDatabase.h"

using namespace std;

class Player {
private:
    string name;
    int HP;
    vector<Card*> deck;
    int mana;
    int maxMana;

public:
    Player(const string& name);
    ~Player();
    vector<Card*> hand;
    vector<Minion*> board; // Minions on the board
    vector<Minion*> graveyard; // Minions in the graveyard
    void drawCard();
    void discardCard(int index);
    void playCard(int index, Player* opponent);
    void playCard(int index, int targetPlayerIndex, int targetMinionIndex, Player* opponent); // Overloaded playCard function
    void attack(int attackerIndex, int targetIndex, Player& opponent);
    void attackHero(int attackerIndex, Player& opponent);
    void useAbility(int minionIndex);
    void addToGraveyard(Minion* minion);
    void endTurn();
    void startTurn();
    const int getHP() const;
    void modifyHP(int amount);
    void showHand() const;
    void showBoard() const;
    void loadDeck(const string& filename, const CardDatabase& cardDatabase);
    void shuffleDeck();
    const string& getName() const;
    bool isBoardFull() const;
};

#endif // PLAYER_H
