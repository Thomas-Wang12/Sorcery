#include "Player.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <random>
#include <chrono>
#include <algorithm>
#include "globals.h"

using namespace std;

Player::Player(const string& name) : name(name), HP(20), mana(3), maxMana(3), hand(), deck(), board(), graveyard() {}

Player::~Player() {
    for (auto card : hand) {
        //delete card;
    }
    for (auto minion : board) {
        //delete minion;
    }
    for (auto minion : graveyard) {
        //delete minion;
    }
}

void Player::drawCard() {
    if (!deck.empty()) {
        Card* card = deck.back();
        deck.pop_back();
        hand.push_back(card);
    }
}

void Player::discardCard(int index) {
    if(index >= 0 && index < hand.size()) {
        hand.erase(hand.begin() + index);
    }
}

void Player::playCard(int index, Player* opponent) {
    if (index >= 0 && index < hand.size()) {
        Card* card = hand[index];
        if(!testing && mana < card->getCost()) {
            return;
        }
        if (Minion* minion = dynamic_cast<Minion*>(card)) {
            if (!isBoardFull()) {
                for (auto& slot : board) {
                    if (slot == nullptr) {
                        slot = minion->clone();
                        hand.erase(hand.begin() + index);
                        mana -= card->getCost();
                        //minion->play(this);
                        break;
                    }
                }
            } else {
                cout << "Board is full!" << endl;
            }
        } else if (Spell* spell = dynamic_cast<Spell*>(card)) {
            // Spell with no target
            spell->spellEffect(this, opponent, 0, 0);
            hand.erase(hand.begin() + index);
            mana -= card->getCost();
        }
    }
}

void Player::playCard(int index, int targetPlayerIndex, int targetMinionIndex, Player* opponent) {
    if (index >= 0 && index < hand.size()) {
        Card* card = hand[index];
        if(!testing && mana < card->getCost()) {
            return;
        }
        if (Spell* spell = dynamic_cast<Spell*>(card)) {
            spell->spellEffect(this, opponent, targetPlayerIndex, targetMinionIndex);
            hand.erase(hand.begin() + index);
            mana -= card->getCost();
        } else {
            std::cout << "This card requires a target." << endl;
        }
    }
}

void Player::attack(int attackerIndex, int targetIndex, Player& opponent) {
    if (attackerIndex < board.size() && board[attackerIndex] != nullptr) {
        Minion* attacker = board[attackerIndex];
        if (targetIndex < opponent.board.size() && opponent.board[targetIndex] != nullptr) {
            Minion* target = opponent.board[targetIndex];
            attacker->attack(target);
            if (!attacker->isAlive()) {
                addToGraveyard(attacker);
                board[attackerIndex] = nullptr;
            }
            if (!target->isAlive()) {
                opponent.addToGraveyard(target);
                opponent.board[targetIndex] = nullptr;
            }
        } else {
            cout << "Invalid target index" << endl;
        }
    } else {
        cout << "Invalid attacker index" << endl;
    }
}

void Player::attackHero(int attackerIndex, Player& opponent) {
    if (attackerIndex < board.size() && board[attackerIndex] != nullptr) {
        Minion* attacker = board[attackerIndex];
        attacker->attackHero(opponent);
        if (opponent.HP <= 0) {
            cout << opponent.getName() << " has been defeated. " << getName() << " wins!" << endl;
        }
    }
}

void Player::addToGraveyard(Minion* minion) {
    graveyard.push_back(new Minion(*minion));
}

bool Player::isBoardFull() const {
    for (const auto& slot : board) {
        if (slot == nullptr) return false;
    }
    return true;
}

void Player::endTurn() {
    // End of turn effects
}

void Player::startTurn() {
    mana = ++maxMana;
    if(hand.size() < 5) drawCard();
    for (auto& minion : board) {
        if (minion) {
            minion->refreshActions();
        }
    }
}

void Player::showHand() const {
    cout << "Magic: " << mana << endl;
    for (int i = 0; i < hand.size(); ++i) {
        cout << i << ": " << hand[i]->getName() << " (Cost: " << hand[i]->getCost() << ")\n";
    }
}

void Player::showBoard() const {
    cout << "Life: " << HP << endl;
    for (int i = 0; i < board.size(); ++i) {
        if (board[i] != nullptr) {
            cout << i << ": " << board[i]->getName() << " (Attack: " << board[i]->getAttack() << ", Health: " << board[i]->getHealth() << ")\n";
        } else {
            cout << i << ": Empty\n";
        }
    }
}

void Player::shuffleDeck() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

void Player::loadDeck(const string& filename, const CardDatabase& cardDatabase) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open deck file: " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        Card* card = cardDatabase.getCard(line);
        if (card) {
            deck.push_back(card); // Use clone to create a deep copy
        } else {
            cout << "Card not found in database: " << line << endl;
        }
    }
    if(!testing) {

        shuffleDeck();
    }

    file.close();
}

const string& Player::getName() const {
    return name;
}


const int Player::getHP() const {
    return HP;
}

void Player::modifyHP(int amount) {
    HP += amount;
}
