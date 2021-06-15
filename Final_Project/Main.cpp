#include "Map.h"
#include "Engine.h"
#include "HiScore.h"

#include <iostream>
#include <stdlib.h>
#include <panel.h>
#include <ncurses.h>
#include <string.h>
#include <fstream>
#include <unistd.h>
#include <iomanip>

using namespace std;

int main(int argc, char ** argv){
	char name[10];
	char word;
	int ch;


	Map map(argv[1]);
	Potter potter(0, 0, 'P', &map);
	Gnome gnome(0, 0, 'G', &map);
	Traal traal(0, 0, 'T', &map);
	HiScore hiscore(argv[2]);
	Engine engine(&map, &potter, &gnome, &traal);

	try{
		if(argc < 3){  // if the user didn't insert map and hiscore files before running then throw exception
			throw "In Main.cpp, you need to have the map and the hiscore files when you are running the game";
		}
		
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
		init_pair(6, COLOR_GREEN, COLOR_GREEN);
		init_pair(7, COLOR_RED, COLOR_RED);
		init_pair(8, COLOR_CYAN, COLOR_CYAN);

		if (has_colors() == false){
			endwin();
			throw "Terminal doen't support colors";
		}

		ifstream start_file;  // printing the name of the game
			start_file.open("game_name.txt");

			if(start_file.fail()){
				cout << "Win error!";
				exit(0);
			}

			start_file >> noskipws;
			while(start_file){
			    start_file >> word;
			    if(word == '|' || word == '_' || word == '/' || word == '=' || word == '\\'){
			        attron(COLOR_PAIR(8));
			        printw("%c", word);
			        attroff(COLOR_PAIR(8));
			    } else {
			        printw("%c", word);
			    }
			}
			start_file.close();

			move(12, 0);
			printw("Press any key to start the game...");
			ch = getch();
			clear();		

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
		clear();																   // if continue_game == 2 then the player lost
		endwin();																   // if continue_game == 3 then the player quitted
																				   
		if(continue_game == 1){  // printing the animation "YOU WON" 
			ifstream win_file;
			win_file.open("you_won.txt");

			if(win_file.fail()){
				cout << "Win error!";
				exit(0);
			}

			initscr();
			clear();
			win_file >> noskipws;
			while(win_file){
			    win_file >> word;
			    if(word == '|' || word == '_' || word == '/' || word == '=' || word == '\\'){
			        attron(COLOR_PAIR(6));
			        printw("%c", word);
			        attroff(COLOR_PAIR(6));
			    } else {
			        printw("%c", word);
			    }
			}
			win_file.close();

			move(12, 0);
			printw("Press any key to continue...");
			ch = getch();

			endwin();
		} else if(continue_game == 2){  // printing the animation "GAME OVER"
			ifstream game_over_file;
			game_over_file.open("game_over.txt");

			if(game_over_file.fail()){
				cout << "Game over error!";
				exit(0);
			}

			initscr();
			start_color();
			game_over_file >> noskipws;
			while(game_over_file){
				game_over_file >> word;
				if(word == '|' || word == '_' || word == '/' || word == '=' || word == '\\' || word == '-'){
					attron(COLOR_PAIR(7));
					printw("%c", word);
					attroff(COLOR_PAIR(7));
				} else {
					printw("%c", word);
				}
			}
			game_over_file.close();

			move(12, 0);
			printw("Press any key to continue...");
			ch = getch();

			endwin();
		} else if(continue_game == 3){
			cout <<  "The user quited." << endl;
		}

	    // read the name of the player
		cout <<  endl << "Enter your name: ";
		cin >> setw(10) >> name;																		   		
	} catch (const char * exc){  // Map exception
		cerr << exc << endl;
	}
	engine.setPlayerName(name);
	hiscore<<engine;  // check if he will be place in the high score table

	return 0;
}	
