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
        vector<int> parchment_cords;  // keeping the parchment's coordinates
        char * player_name;  // the name of the player
        int player_score;  // the score of the player
        vector<int> gnome_stepped_on_a_stone;  // these vectors are needed to check if the monsters are on a stone
        vector<int> traal_stepped_on_a_stone;
        int gnome_stepped_on_parchment;  // those flags are needed to check if the monsters are on the parchment
        int traal_stepped_on_parchment;
    public:
        Engine(Map *, Potter *, Gnome *, Traal *);
        void placeEveryone();  // placing Potter, Traal, Gnome and the stones in the map
        int getNewCoordinates();  // checks if the new coordinates are valid
        void placeParchment();  // when stones.size() == 0 then we'll call this function to place the parchment

        int getAmountOfStones() const;  // getting the amount of stones that are in the map
        int getPlayerScore() const;  // getter and setter for player's score
        void setPlayerScore(int);
        char * getPlayerName() const;  // getter and setter for player's name
        void setPlayerName(const char *);
};

#endif