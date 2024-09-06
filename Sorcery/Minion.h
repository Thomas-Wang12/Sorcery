#ifndef MINION_H
#define MINION_H

#include "Card.h"

using namespace std;

class Minion : public Card {
private:
    //std::string name; //This was the issue before
    string description;
    //int cost;
    int attackValue;
    int healthValue;
    int numberOfActions;

public:
    Minion(string name, string description, int cost, int attack, int health);
    Minion(const Minion& other);
    Minion& operator=(const Minion& other); // Assignment operator
    string getName() const;
    string getDescription() const;
    int getCost() const;
    int getAttack() const;
    int getHealth() const;
    void setHealth(int health);
    void play(Player* player) override;
    void attack(Minion* target);
    void attackHero(Player& player);
    void useAbility();
    void takeDamage(int amount);
    void refreshActions();
    bool isAlive() const;
    Minion* clone() const override;
};

#endif // MINION_H
