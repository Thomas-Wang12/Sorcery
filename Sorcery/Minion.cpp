#include "Minion.h"
#include "Player.h"
#include <iostream>

using namespace std;

Minion::Minion(std::string name, std::string description, int cost, int attack, int health)
    : Card(name, cost), description(description), attackValue(attack), healthValue(health), numberOfActions(0) {}


Minion::Minion(const Minion& other)
    : Card(other), description(other.description), attackValue(other.attackValue), healthValue(other.healthValue), numberOfActions(0) {}

Minion& Minion::operator=(const Minion& other) {
    if (this != &other) {
        Card::operator=(other);
        description = other.description;
        attackValue = other.attackValue;
        healthValue = other.healthValue;
        numberOfActions = other.numberOfActions;
    }
    return *this;
}


std::string Minion::getName() const {
    return name;
}

std::string Minion::getDescription() const {
    return description;
}

int Minion::getCost() const {
    return cost;
}

int Minion::getAttack() const {
    return attackValue;
}

int Minion::getHealth() const {
    return healthValue;
}

void Minion::setHealth(int health) {
    healthValue = health;
}


void Minion::play(Player* player) {
    // When minion is played
}


void Minion::attack(Minion* target) {
    if (numberOfActions > 0 && target->isAlive()) {
        target->takeDamage(attackValue);
        takeDamage(target->getAttack());
        numberOfActions--;
    } else {
        cout << "That minion has no actions." << endl;
    }
}

void Minion::attackHero(Player& opponent) {
    if (numberOfActions > 0) {
        opponent.modifyHP(-attackValue);
        numberOfActions--;
    } else {
        cout << "That minion has no actions." << endl;
    }
}

void Minion::useAbility() {
    if (numberOfActions > 0) {
        // Use Ability
    }
}

void Minion::takeDamage(int amount) {
    healthValue -= amount;
    if (healthValue < 0) {
        healthValue = 0;
    }
}
void Minion::refreshActions() {
    numberOfActions = 1;
}
bool Minion::isAlive() const {
    return healthValue > 0;
}


Minion* Minion::clone() const {
    return new Minion(*this);
}
