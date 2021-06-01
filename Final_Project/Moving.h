#ifndef Moving_h
#define Moving_h

#include "Map.h"

#include <ncurses.h>

using namespace std;

class Moving{
    protected:
        int x;
        int y;
        char symbol;
        Map * map;
    public:
        Moving(int, int, char);

        int getX() const;
        int getY() const;

        void setX(const int);
        void setY(const int);

        char getSymbol() const;
        
        // virtual void move() = 0;  //  will it be void?
};

#endif