#ifndef Engine_h
#define Engine_h

#include "Map.h"
#include "Potter.h"
#include "Gnome.h"
#include "Traal.h"

using namespace std;

class Engine{
    private:
        Map * map;
        Potter * potter;  // or vector<Moving *>
        Gnome * gnome;
        Traal * traal;
        vector<char> stones;
        // vector<int> stones_cords;
        char parchment;
        // vector<int> parchment_cords;
        // i have to store the coordinates of the stones  
    public:
        Engine(Map *, Potter *, Gnome *, Traal *);
        void placeEveryone();
        void placeParchment();  // when stones.size() == 0 then we'll call this function to place the parchment
        void getNewCoordinates();  // checks if the new coordinates are valid
};

#endif