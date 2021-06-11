#ifndef Traal_h
#define Traal_h

#include "Moving.h"
#include "Map.h"

using namespace std;

class Traal: public Moving{
    public:
        Traal(int, int, char, Map *);
        vector<int> moveCharacter();
};

#endif