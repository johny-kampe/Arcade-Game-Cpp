#include "Map.h"
#include "Engine.h"
#include "HiScore.h"

#include <iostream>
#include <stdlib.h>
#include <panel.h>
#include <ncurses.h>
#include <string.h>

using namespace std;

int main(int argc, char ** argv){
	try{
		if(argc < 3){  // if the user didn't insert map and hiscore files before running then throw exception
			throw "In Main.cpp, you need to have the map and the hiscore files when you are running the game";
		}

		Map map(argv[1]);
		Potter potter(0, 0, 'P', &map);
		Gnome gnome(0, 0, 'G', &map);
		Traal traal(0, 0, 'T', &map);
		HiScore hiscore(argv[2]);
		Engine engine(&map, &potter, &gnome, &traal);
		
		vector<string> mapp = map.getMap();

		initscr(); 
		noecho();  // any other key except Up, Down, Left, Right, Space and Escape have no effect in the game
		keypad (stdscr,TRUE);  // special buttons (Esc, Space, Pg Up etc.)
		curs_set(0);  // to make cursor disappear

		start_color();  // setting colors
		init_pair(1, COLOR_BLACK, COLOR_GREEN);
		init_pair(2, COLOR_BLACK, COLOR_RED);
		init_pair(3, COLOR_BLACK, COLOR_YELLOW);
		init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA);
		init_pair(5, COLOR_BLACK, COLOR_WHITE);

		if (has_colors() == false){
			endwin();
			throw "Terminal doen't support colors";
		}

		for(int i = 0; i < map.getRows(); i++){  // here we print the wall and we change the color to brown
			for (int j = 0; j < map.getColumns(); j++){
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
		if(continue_game == 1){
			cout << "YOU WON" << endl;
		} else if(continue_game == 2){
			cout << "GAME OVER" << endl;
		} else if(continue_game == 3){
			cout <<  "The user quited." << endl;
		}

		char name[11];  // read the name of the player
		cout <<  endl << "Enter your name: ";
		cin >> name;																		   
		engine.setPlayerName(name);

		hiscore<<engine;  // check if he will be place in the high score table
		
		return 0;

	} catch (const char * exc){  // Map exception
		cerr << exc << endl;
	}
}	
