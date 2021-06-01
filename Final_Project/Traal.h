#ifndef Traal_h
#define Traal_h

#include "Moving.h"
#include "Map.h"

using namespace std;

class Traal: public Moving{
    private:
        // Map * map;
    public:
        Traal(int, int, char);
        void move();
};

#endif