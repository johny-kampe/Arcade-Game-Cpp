#include "Engine.h"

#include <iostream>
#include <vector>
#include <time.h>
#include <ncurses.h>

Engine::Engine(Map * mapp, Potter * pot, Gnome * gn, Traal * tr){
    map = mapp;
    potter = pot;
    gnome = gn;
    traal = tr;

    for (int i = 0; i < 10; i++){
        stones.push_back('$');
    }
    
    parchment = '@';
}

void Engine::placeEveryone(){
    srand (time(NULL));
    int x = 0;
    int y = 0;
    int flag; // i need the flag to check if there is any other symbol ('P', 'G' etc.)
    vector<int> taken;

    vector<string> place_map = map->getMap();

    for(int i = 0; i < 3; i++){  // adding potter, gnome and traal in map, now we have to insert the pergamines
        do{
            flag = 0; // initialize the flag
            x = rand() % 18 + 1;  // random row
            y = rand() % 58 + 1;  // ramndom column

            if(taken.size() > 0){  // if there isn't any character in the game, move on
                for (int j = 0; j < taken.size(); j++){  // check if those coordinates are already taken 
                    if(taken[j] == x || taken[j] == y){  // if they are change the flag
                        flag++;
                    }
                }
            }
        }while(place_map[x][y] == '*' || flag != 0);  // if in the given coordinates is a wall or another symbol produxe new random numbers 

        taken.push_back(x);  // insert every taken coordinate in the vector
        taken.push_back(y);

        move(x, y);
        if (i == 0){  // at the first loop we put Potter in the game
            potter->setX(x);
            potter->setY(y);
            addch(potter->getSymbol());
        } else if(i == 1){  // at the second loop we put Gnome in the game
            potter->setX(x);
            potter->setY(y);
            addch(gnome->getSymbol());
        } else if(i == 2){  // at the first loop we put Traal in the game
            potter->setX(x);
            potter->setY(y);
            addch(traal->getSymbol());
        }  
        
        // here i will put the stones too
    
    }

    refresh();
}

void Engine::getNewCoordinates(){
    vector<int> new_cords;
    new_cords = potter->moveCharacter();

    // if(new_cords[i] == ){
        
    // }
}


