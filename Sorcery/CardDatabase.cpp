#include "CardDatabase.h"
#include "Minion.h"
#include "Spell.h"

using namespace std;

CardDatabase::CardDatabase() {
    cardMap["Air Elemental"] = new Minion("Air Elemental", "", 0, 1, 1);
    cardMap["Water Elemental"] = new Minion("Water Elemental", "", 1, 2, 2);
    cardMap["Earth Elemental"] = new Minion("Earth Elemental", "", 3, 4, 4);
    cardMap["Dark Sorcerer"] = new Minion("Dark Sorcerer", "", 7, 8, 8);
    cardMap["Banish"] = new Banish();
    cardMap["Unsummon"] = new Unsummon();
    //cardMap["Recharge"] = new Recharge();
    //cardMap["Disenchant"] = new Disenchant();
    cardMap["Raise Dead"] = new RaiseDead();
    cardMap["Blizzard"] = new Blizzard();

}

CardDatabase::~CardDatabase() {
    for (auto& pair : cardMap) {
        delete pair.second;
    }
}

Card* CardDatabase::getCard(const string& name) const {
    auto it = cardMap.find(name);
    if (it != cardMap.end()) {
        return it->second;
    }
    return nullptr;
}

