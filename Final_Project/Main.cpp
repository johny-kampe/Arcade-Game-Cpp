#include "Map.h"
#include "Engine.h"
#include "HiScore.h"

#include <iostream>
#include <stdlib.h>
#include <panel.h>
#include <ncurses.h>

using namespace std;

int main(int argc, char ** argv){
    Map * map = new Map(argv[1]);
	Potter * potter = new Potter(0, 0, 'P', map);
	Gnome * gnome = new Gnome(0, 0, 'G', map);
	Traal * traal = new Traal(0, 0, 'T', map);
	HiScore * hiscore = new HiScore(argv[2]);

    vector<string> mapp = map->getMap();

	Engine engine(map, potter, gnome, traal);

    // initscr();
	// noecho();
	// keypad (stdscr,TRUE);  // special buttons (Esc, Space, Pg Up etc.)
	// curs_set(0);
	
	// for(int i = 0; i < map->getRows(); i++){
	// 		for (int j = 0; j < map->getColumns(); j++){
	// 			move(i, j);
	// 			addch(mapp[i][j]);
	// 		}
	// 	}
	// engine.placeEveryone();
	// refresh();

	// int ch;
	// int amount_of_stones;
	// int flag_parchment = 0;  // this flag is needed so the following if will never run again
	// int continue_game = 0;

	// do {
	// 	continue_game = engine.getNewCoordinates();
	// 	refresh();
	// 	// engine.getNewCoordinates();
	// 	amount_of_stones = engine.getAmountOfStones();

	// 	if (amount_of_stones == 0 && flag_parchment == 0){  // if every stone has been collected then place a parchment
	// 		engine.placeParchment();
	// 		flag_parchment++;
	// 	}
	// } while (continue_game != 1);
	// endwin();

	cout << "I was in main!!. Ending the program!" << endl;

	delete map;
	delete potter;
	delete gnome;
	delete traal;

	cout << "All good!" << endl;

    return 0;
}

// cout << "The main club! " << mapp.size() << endl;
    // for(int i = 0; i < mapp.size(); i++){
    //     cout << mapp[i];
    // }

// int curx, cury;
	// int ch;
	// curx = cury = 10;
	// initscr ();
	// printw ("Hello world\n");  
	// refresh ();  // clears the terminal
	// getch ();  // gets the char
	// clear ();  
	// keypad (stdscr,TRUE);  // special buttons (Esc, Space, Pg Up etc.)
	// move(cury, curx);  // 
	// addch ('C');
	// do { // waits for a character	
	// 	ch = getch ();
	// 	move(cury, curx);
	// 	addch (' ');
	// 	switch (ch){
	// 		case KEY_UP : cury--; break;
	// 		case KEY_DOWN : cury++; break;
	// 		case KEY_LEFT: curx--; break;
	// 		case KEY_RIGHT: curx++; break;
	// 	}
	// 	move(cury, curx);
	// 	addch ('C');
	// }while (ch != 27);  // Esc ASCII
	// endwin ();

/*

#include <stdlib.h>     // srand, rand 
#include <time.h>       // time 

placeToMap(){
    srand (time(NULL));  // initialize random seed:

    //  v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014
    rand() % 1077 + 61;
}

// what ncurses does with x and y? how i will write potter in map?
// will i use number of chars or x,y?

*/