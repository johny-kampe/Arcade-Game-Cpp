#ifndef Gnome_h
#define Gnome_h

#include "Moving.h"
#include "Map.h"

using namespace std;

class Gnome: public Moving{
    private:
        // Map * map;        
    public:
        Gnome(int, int, char);
        void map();
};

#endif