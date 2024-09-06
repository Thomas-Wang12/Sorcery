#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

class Player;

class Card {
protected:
    string name;
    int cost;

public:
    Card(const string& name, int cost);
    virtual ~Card() = default;
    Card(const Card& other); // Copy constructor
    Card& operator=(const Card& other); //Copy assignment

    string getName() const;
    int getCost() const;
    virtual void play(Player* player) = 0;
    virtual Card* clone() const = 0;

};

class Spell : public Card {
public:
    Spell(const string& name, int cost);
    Spell(const Spell& other); // Copy constructor
    Spell& operator=(const Spell& other); // Assignment operator
    virtual void spellEffect(Player* player, Player* opponent, int targetPlayerIndex, int targetMinionIndex) = 0;
    void play(Player* player) override;
    Card* clone() const override = 0;
};

#endif // CARD_H
