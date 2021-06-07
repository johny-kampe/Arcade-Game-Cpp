#ifndef Gnome_h
#define Gnome_h

#include "Moving.h"
#include "Map.h"

using namespace std;

class Gnome: public Moving{       
    public:
        Gnome(int, int, char, Map *);
        void map();
        vector<int> moveCharacter();
};

#endif