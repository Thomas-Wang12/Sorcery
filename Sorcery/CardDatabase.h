#ifndef CARDDATABASE_H
#define CARDDATABASE_H

#include <unordered_map>
#include <string>
#include "Card.h"

using namespace std;

class CardDatabase {
private:
     unordered_map<string, Card*> cardMap;

public:
    CardDatabase();
    ~CardDatabase();
    Card* getCard(const string& name) const;
};

#endif // CARDDATABASE_H

