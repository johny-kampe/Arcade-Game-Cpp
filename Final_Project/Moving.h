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
        Map * moving_map;
    public:
        Moving(int, int, char, Map *);
        virtual ~Moving();

        int getX() const;
        int getY() const;

        void setX(const int);
        void setY(const int);

        char getSymbol() const;
        
        virtual vector<int> moveCharacter() = 0;  // every child must move
};

#endif