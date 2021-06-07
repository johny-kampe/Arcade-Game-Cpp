#ifndef Engine_h
#define Engine_h

#include "Map.h"
#include "Potter.h"
#include "Gnome.h"
#include "Traal.h"

using namespace std;

class Engine{
    private:
        Map * map;  // points to Map object 
        Potter * potter;  // points to Potter object 
        Gnome * gnome;  // points to Gnome object 
        Traal * traal;  // points to Traal object 
        vector<char> stones;  // keeping the amount stones
        char stone;  // stone's symbol
        vector<int> stones_cords;  // keeping every stone's coordinates
        char parchment;  // parchment's symbol
        // vector<int> parchment_cords;  // keeping the parchment's coordinates
    public:
        Engine(Map *, Potter *, Gnome *, Traal *);
        void placeEveryone();
        bool getNewCoordinates();  // checks if the new coordinates are valid
        void placeParchment();  // when stones.size() == 0 then we'll call this function to place the parchment

        int getAmountOfStones() const;
};

#endif