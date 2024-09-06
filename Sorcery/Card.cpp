#include "Card.h"

using namespace std;

Card::Card(const string& name, int cost) : name(name), cost(cost) {}

Card::Card(const Card& other) : name(other.name), cost(other.cost) {}

Card& Card::operator=(const Card& other) {
    if (this != &other) {
        name = other.name;
        cost = other.cost;
    }
    return *this;
}

string Card::getName() const {
    return name;
}

int Card::getCost() const {
    return cost;
}

void Card::play(Player* player) {
    // Battlecries?
}

Spell::Spell(const string& name, int cost) : Card(name, cost) {}

void Spell::play(Player* player) {

}
