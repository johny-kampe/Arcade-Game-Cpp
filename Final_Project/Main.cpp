#include "Map.h"
#include "Engine.h"
#include "HiScore.h"

#include <iostream>
#include <stdlib.h>
#include <panel.h>
#include <ncurses.h>

using namespace std;

// void operator<< (HiScore &hisco, char name, int score){
// 
// }

int main(int argc, char ** argv){
    Map * map = new Map(argv[1]);
	Potter * potter = new Potter(0, 0, 'P', map);
	Gnome * gnome = new Gnome(0, 0, 'G', map);
	Traal * traal = new Traal(0, 0, 'T', map);
	HiScore * hiscore = new HiScore(argv[2]);

    vector<string> mapp = map->getMap();

	Engine engine(map, potter, gnome, traal);

    initscr(); 
	noecho();
	keypad (stdscr,TRUE);  // special buttons (Esc, Space, Pg Up etc.)
	curs_set(0);

	start_color();  // setting colors
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	init_pair(4, COLOR_CYAN, COLOR_CYAN);
	init_color(COLOR_CYAN, 200, 100, 50);  // i tried to change the cyan color and make it brown to remind us more of a wall
	init_pair(5, COLOR_BLACK, COLOR_MAGENTA);

	for(int i = 0; i < map->getRows(); i++){  // here we print the wall and we change the color to brown
		for (int j = 0; j < map->getColumns(); j++){
			move(i, j);
			if(mapp[i][j] == '*'){
				attron(COLOR_PAIR(4));
				printw("%c", '*');
				attroff(COLOR_PAIR(4));
			} else {
				addch(mapp[i][j]);
			}
		}
	}
	engine.placeEveryone();
	refresh();

	int ch;
	int amount_of_stones;  // we need variable this to check the amount of stones 
	int flag_parchment = 0;  // this flag is needed so the following if will never run again
	int continue_game = 0; // we need this variable to check if the player won, lost or quitted

	do {
		continue_game = engine.getNewCoordinates();
		refresh();
		amount_of_stones = engine.getAmountOfStones();

		if (amount_of_stones == 0 && flag_parchment == 0){  // if every stone has been collected then place a parchment
			engine.placeParchment();
			flag_parchment++;
		}
	} while (continue_game != 1 && continue_game != 2 && continue_game != 3);  // if continue_game == 1 then the player won
	endwin();																   // if continue_game == 2 then the player lost
																			   // if continue_game == 3 then the player quitted
	
	// hiscore << engine.getPlayerName() << engine.getPlayerScore();
	
	if(continue_game == 1){
		cout << "YOU WON" << endl;
	} else if(continue_game == 2){
		cout << "GAME OVER" << endl;
	} else if(continue_game == 3){
		cout <<  "The user quited." << endl;
	}

	delete map;
	delete potter;
	delete gnome;
	delete traal;

    return 0;
}	
