#include "Engine.h"

#include <iostream>
#include <vector>
#include <time.h>
#include <ncurses.h>

Engine::Engine(Map * mapp, Potter * pot, Gnome * gn, Traal * tr): map(mapp), potter(pot), gnome(gn), traal(tr), player_score(0){
    stone = '$';
    for (int i = 0; i < 10; i++){
        stones.push_back(stone);
    }
    
    parchment = '@';
    gnome_stepped_on_parchment = 0;
    traal_stepped_on_parchment = 0;
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
                for (int j = 0; j < taken.size(); j+=2){  // check if those coordinates are already taken 
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
            // addch(potter->getSymbol());
            attron(COLOR_PAIR(1));
            printw("%c", potter->getSymbol());
            attroff(COLOR_PAIR(1));
        } else if(i == 1){  // at the second loop we put Gnome in the game
            gnome->setX(x);
            gnome->setY(y);
            // addch(gnome->getSymbol());
            attron(COLOR_PAIR(2));
            printw("%c", gnome->getSymbol());
            attroff(COLOR_PAIR(2));
        } else if(i == 2){  // at the third loop we put Traal in the game
            traal->setX(x);
            traal->setY(y);
            // addch(traal->getSymbol());
            attron(COLOR_PAIR(2));
            printw("%c", traal->getSymbol());
            attroff(COLOR_PAIR(2));
        } else if(i >= 3){  // at the forth loop and after we put the stones in the game
            stones_cords.push_back(x);
            stones_cords.push_back(y);
            // addch(stone);
            attron(COLOR_PAIR(3));
            printw("%c", stone);
            attroff(COLOR_PAIR(3));
        }
    }
    refresh();
}

int Engine::getNewCoordinates(){
    int counter = 0;
    int flag = 0;
    vector<int> new_cords;

    vector<string> check_map = map->getMap();

    // ******************************** Place Potter ********************************
    do{  // check if in the new coordinates is a wall
        new_cords = potter->moveCharacter();  // call the function to move potter 
        if(new_cords[0] == -1 && new_cords[1] == -1){  // if the user pressed the 'End Game' combination values then change the flag and break the loop
            flag++;
            break;
        }
    }while(check_map[new_cords[0]][new_cords[1]] == '*'); 

    if(flag == 1){  // if the flag is 1 then return 3 and end the game
        return 3;
    }

    move(potter->getX(), potter->getY());
	if((new_cords[0] == traal->getX() && new_cords[1] == traal->getY()) || (new_cords[0] == gnome->getX() && new_cords[1] == gnome->getY())){
        return 2;
    } 
    
    addch (' ');

    if(parchment_cords.size() != 0){  // if the parchment is in the map then
        if(new_cords[0] == parchment_cords[0] && new_cords[1] == parchment_cords[1]){  // check if in the new coordinates is the parchment
            this->setPlayerScore(100);  // if it is add 100 points to score and end the program because the player just won
            return 1;
        }
    }

    for (int j = 0; j < stones_cords.size(); j+=2){  // check if in the new coordinates is a stone
        if(stones_cords[j] == new_cords[0] && stones_cords[j+1] == new_cords[1]){  // if there is a stone then erase it and add 10 points 
            stones_cords.erase(stones_cords.begin()+j);
            stones_cords.erase(stones_cords.begin()+j);
            stones.erase(stones.begin());
            this->setPlayerScore(10);
            break;
        }
    }
    move(map->getRows()+1, 0);  // move below the map and print the current score
    printw("Score: %d", this->getPlayerScore());

    move(new_cords[0], new_cords[1]);  // move to potter to the new coordinates and print him in the map
    attron(COLOR_PAIR(1));
    printw("%c", potter->getSymbol());
    attroff(COLOR_PAIR(1));

    potter->setX(new_cords[0]);  // setting the new valid coordinates to Potter 
    potter->setY(new_cords[1]);

    // ******************************** Place Gnome ********************************
    do{  // check if in the new coordinates is a wall
        new_cords = gnome->moveCharacter();
    }while(check_map[new_cords[0]][new_cords[1]] == '*');

    move(gnome->getX(), gnome->getY());

    if(new_cords[0] == potter->getX() && new_cords[1] == potter->getY()){  // if in the new coordinates is potter then end the game
        return 2;
    } 
    
    if(gnome_stepped_on_a_stone.size() != 0){  // if gnome stepped before in a stone then print it again 
        attron(COLOR_PAIR(3));
        printw("%c", stone);
        attroff(COLOR_PAIR(3));
        gnome_stepped_on_a_stone.erase(gnome_stepped_on_a_stone.begin());
        gnome_stepped_on_a_stone.erase(gnome_stepped_on_a_stone.begin());
    } else if (gnome_stepped_on_parchment == 1){  // if gnome stepped before in the parchment then print it again
        attron(COLOR_PAIR(5));
        printw("%c", parchment);
        attroff(COLOR_PAIR(5));
        gnome_stepped_on_parchment = 0;   
    } else {  // else print space
	    addch (' ');
    }

    move(new_cords[0], new_cords[1]);
    for (int j = 0; j < stones_cords.size(); j+=2){  // check if in the new coordinates is a stone
        if(stones_cords[j] == new_cords[0] && stones_cords[j+1] == new_cords[1]){  // if there is a stone then keep it's coordinates 
            gnome_stepped_on_a_stone.push_back(new_cords[0]);
            gnome_stepped_on_a_stone.push_back(new_cords[1]);            
            break;
        }
    }

    if(parchment_cords.size() != 0){  // if the parchment is in the map then
        if(new_cords[0] == parchment_cords[0] && new_cords[1] == parchment_cords[1]){  // check if in the new coordinates is the parchment
            gnome_stepped_on_parchment = 1;  // if it is then change gnome's flag 
        }
    }

    attron(COLOR_PAIR(2));
    printw("%c", gnome->getSymbol());
    attroff(COLOR_PAIR(2));

    gnome->setX(new_cords[0]);  // setting the new valid coordinates to Gnome
    gnome->setY(new_cords[1]);

    // ******************************** Place Traal ********************************
    do{  // check if in the new coordinates is a wall
        new_cords = traal->moveCharacter();
    }while(check_map[new_cords[0]][new_cords[1]] == '*');

    move(traal->getX(), traal->getY());

    if(new_cords[0] == potter->getX() && new_cords[1] == potter->getY()){  // if in the new coordinates is potter then end the game
        return 2;
    } 

    if(traal_stepped_on_a_stone.size() != 0){  // if traal stepped before in a stone then print it again 
        attron(COLOR_PAIR(3));
        printw("%c", stone);
        attroff(COLOR_PAIR(3));
        traal_stepped_on_a_stone.erase(traal_stepped_on_a_stone.begin());
        traal_stepped_on_a_stone.erase(traal_stepped_on_a_stone.begin());
    } else if (traal_stepped_on_parchment == 1){  // if traal stepped before in the parchment then print it again
        attron(COLOR_PAIR(5));
        printw("%c", parchment);
        attroff(COLOR_PAIR(5));
        traal_stepped_on_parchment = 0;   
    } else {  // else print space
	    addch (' ');
    }

    move(new_cords[0], new_cords[1]);
    for (int j = 0; j < stones_cords.size(); j+=2){  // check if in the new coordinates is a stone
        if(stones_cords[j] == new_cords[0] && stones_cords[j+1] == new_cords[1]){  // if there is a stone then keep it's coordinates 
            traal_stepped_on_a_stone.push_back(new_cords[0]);
            traal_stepped_on_a_stone.push_back(new_cords[1]);            
            break;
        }
    }

    if(parchment_cords.size() != 0){  // if the parchment is in the map then
        if(new_cords[0] == parchment_cords[0] && new_cords[1] == parchment_cords[1]){  // check if in the new coordinates is the parchment
            traal_stepped_on_parchment = 1;  // if it is then change gnome's flag 
        }
    }

    attron(COLOR_PAIR(2));
    printw("%c", traal->getSymbol());
    attroff(COLOR_PAIR(2));

    traal->setX(new_cords[0]);  // setting the new valid coordinates to Traal 
    traal->setY(new_cords[1]);

    return 0;
}

void Engine::placeParchment(){
    srand (time(NULL));
    int x = 0;
    int y = 0;

    vector<string> place_map = map->getMap();

    do{
        x = rand() % 18 + 1;  // random row
        y = rand() % 58 + 1;  // ramndom column            
    }while(place_map[x][y] == '*' || (x == traal->getX() && y == traal->getY()) || (x == gnome->getX() && y == gnome->getY()));  // if in the given coordinates is a wall or another symbol produce new coordinates 

    parchment_cords.push_back(x);  // insert every taken coordinate in the vector
    parchment_cords.push_back(y);

    move(x, y);
    attron(COLOR_PAIR(5));
    printw("%c", parchment);
    attroff(COLOR_PAIR(5));

}   

int Engine::getAmountOfStones() const{
    return stones.size();
}

int Engine::getPlayerScore() const{
    return player_score;
}

void Engine::setPlayerScore(int score){
    player_score += score;
}

char Engine::getPlayerName() const{
    return player_name;
}