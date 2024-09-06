#include "Spell.h"
#include "Player.h"
#include "Minion.h"
#include <iostream>

using namespace std;

Spell::Spell(const Spell& other) : Card(other) {}

Spell& Spell::operator=(const Spell& other) {
    if (this != &other) {
        Card::operator=(other);
    }
    return *this;
}

Banish::Banish() : Spell("Banish", 2) {}

void Banish::spellEffect(Player* player, Player* opponent, int targetPlayerIndex, int targetMinionIndex) {
    Player* targetPlayer = (targetPlayerIndex == 1) ? player : opponent;
    if (targetMinionIndex >= 0 && targetMinionIndex < targetPlayer->board.size()) {
        //delete targetPlayer->board[targetMinionIndex];
        targetPlayer->board[targetMinionIndex] = nullptr;
    }
}

Card* Banish::clone() const {
    return new Banish(*this);
}

Unsummon::Unsummon() : Spell("Unsummon", 1) {}

void Unsummon::spellEffect(Player* player, Player* opponent, int targetPlayerIndex, int targetMinionIndex) {
    Player* targetPlayer = (targetPlayerIndex == 1) ? player : opponent;
    if (targetMinionIndex >= 0 && targetMinionIndex < targetPlayer->board.size()) {
        Card* minion = targetPlayer->board[targetMinionIndex];
        if (minion) {
            targetPlayer->hand.push_back(minion);
            targetPlayer->board[targetMinionIndex] = nullptr;
        }
    }
}

Card* Unsummon::clone() const {
    return new Unsummon(*this);
}

RaiseDead::RaiseDead() : Spell("Raise Dead", 1) {}

void RaiseDead::spellEffect(Player* player, Player* opponent, int targetPlayerIndex, int targetMinionIndex) {
    if (!player->graveyard.empty()) {
        Minion* minion = player->graveyard.back();
        player->graveyard.pop_back();
        minion->setHealth(1); // Set health to 1
        for (auto& slot : player->board) {
            if (slot == nullptr) {
                slot = minion->clone();
                break;
            }
        }
    }
}

Card* RaiseDead::clone() const {
    return new RaiseDead(*this);
}

Blizzard::Blizzard() : Spell("Blizzard", 3) {}

void Blizzard::spellEffect(Player* player, Player* opponent, int targetPlayerIndex, int targetMinionIndex) {
    for (auto& minion : player->board) {
        if (minion) {
            minion->takeDamage(2);
            if (!minion->isAlive()) {
                player->addToGraveyard(minion);
                minion = nullptr;
            }
        }
    }
    for (auto& minion : opponent->board) {
        if (minion) {
            minion->takeDamage(2);
            if (!minion->isAlive()) {
                opponent->addToGraveyard(minion);
                minion = nullptr;
            }
        }
    }
}

Card* Blizzard::clone() const {
    return new Blizzard(*this);
}
