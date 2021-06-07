#ifndef Traal_h
#define Traal_h

#include "Moving.h"
#include "Map.h"

using namespace std;

class Traal: public Moving{
    public:
        Traal(int, int, char, Map *);
        void move();
        vector<int> moveCharacter();
};

#endif