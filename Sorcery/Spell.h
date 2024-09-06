#ifndef SPELL_H
#define SPELL_H

#include "Card.h"

class Banish : public Spell {
public:
    Banish();
    void spellEffect(Player* player, Player* opponent, int targetPlayerIndex, int targetMinionIndex) override;
    Card* clone() const override;
};

class Unsummon : public Spell {
public:
    Unsummon();
    void spellEffect(Player* player, Player* opponent, int targetPlayerIndex, int targetMinionIndex) override;
    Card* clone() const override;
};

class RaiseDead : public Spell {
public:
    RaiseDead();
    void spellEffect(Player* player, Player* opponent, int targetPlayerIndex, int targetMinionIndex) override;
    Card* clone() const override;
};

class Blizzard : public Spell {
public:
    Blizzard();
    void spellEffect(Player* player, Player* opponent, int targetPlayerIndex, int targetMinionIndex) override;
    Card* clone() const override;
};

#endif // SPELL_H
