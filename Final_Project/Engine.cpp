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

    stone = '$';
    for (int i = 0; i < 10; i++){
        stones.push_back(stone);
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

    for(int i = 0; i < 13; i++){  // adding potter, gnome and traal in map, now we have to insert the pergamines
        do{
            flag = 0; // initialize the flag
            x = rand() % 18 + 1;  // random row
            y = rand() % 58 + 1;  // ramndom column

            if(taken.size() > 0){  // if there isn't any character in the game, move on
                for (int j = 0; j < taken.size()/2; j+=2){  // check if those coordinates are already taken 
                    if(taken[j] == x && taken[j+1] == y){  // if they are change the flag
                        flag++;
                    }
                }
            }
        }while(place_map[x][y] == '*' || flag != 0);  // if in the given coordinates is a wall or another symbol produce new coordinates 

        taken.push_back(x);  // insert every taken coordinate in the vector
        taken.push_back(y);

        move(x, y);
        if (i == 0){  // at the first loop we put Potter in the game
            potter->setX(x);
            potter->setY(y);
            addch(potter->getSymbol());
        } else if(i == 1){  // at the second loop we put Gnome in the game
            gnome->setX(x);
            gnome->setY(y);
            addch(gnome->getSymbol());
        } else if(i == 2){  // at the third loop we put Traal in the game
            traal->setX(x);
            traal->setY(y);
            addch(traal->getSymbol());
        } else if(i >= 3){  // at the forth loop and after we put the stones in the game
            stones_cords.push_back(x);
            stones_cords.push_back(y);
            addch(stone);
        }
    }

    refresh();
}

void Engine::getNewCoordinates(){
    int counter = 0;
    // int amount = stones_cords.size()/2;   // ** FOR STONES AND PARCHMENTS
    vector<int> new_cords;

    vector<string> check_map = map->getMap();

    do{  // first stage, check if in the new coordinates is a wall or a monster
        new_cords = potter->moveCharacter();
        printw("FINAL");
    }while(/*new_cords[0] != -1 || */check_map[new_cords[0]][new_cords[1]] == '*' || (new_cords[0] == traal->getX() && new_cords[1] == traal->getY()) || (new_cords[0] == gnome->getX() && new_cords[1] == gnome->getY())); 
        printw("OUTSIDE");
    // if (new_cords[0] == -1){
    //     return 1;
    // }
    

    // while (counter != amount){  // ** second stage, check if there are stones or parchments in the new coordinates 
    //     if(stones_cords[counter] == new_cords[0] && stones_cords[counter+1] == new_cords[1]){

    //     } 
    //     counter++;
    // }
    // if(parchment_cords[0] == new_cords[0] && parchment_cords[0] == new_cords[1]){

    // }

    // printw("HELLO!!");
    move(potter->getX(), potter->getY());  // ** first i check then i change (Engine function checks and changes)
	addch (' ');
    move(new_cords[0], new_cords[1]);
	addch (potter->getSymbol());
    
    potter->setX(new_cords[0]);  // setting the new valid coordinates to Potter 
    potter->setY(new_cords[1]);


    do{  // third stage, check if in the new coordinates is a wall
        new_cords = gnome->moveCharacter();
    }while(check_map[new_cords[0]][new_cords[1]] == '*');

    // what will happen if at the new coordinates is a stone/parchment or the Potter?

    move(gnome->getX(), gnome->getY());  // ** first i check then i change (Engine function checks and changes)
	addch (' ');
    move(new_cords[0], new_cords[1]);
	addch (gnome->getSymbol());

    gnome->setX(new_cords[0]);  // setting the new valid coordinates to Potter 
    gnome->setY(new_cords[1]);


    do{  // third stage, check if in the new coordinates is a wall
        new_cords = traal->moveCharacter();
    }while(check_map[new_cords[0]][new_cords[1]] == '*');

    move(traal->getX(), traal->getY());  // ** first i check then i change (Engine function checks and changes)
	addch (' ');
    move(new_cords[0], new_cords[1]);
	addch (traal->getSymbol());

    traal->setX(new_cords[0]);  // setting the new valid coordinates to Potter 
    traal->setY(new_cords[1]);

    // return 0;

}

void Engine::placeParchment(){
    printw("Placing parchment!");
}

int Engine::getAmountOfStones() const{
    return stones.size();
}
