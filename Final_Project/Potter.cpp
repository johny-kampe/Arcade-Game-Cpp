#include "Potter.h"

#include <stdlib.h>


Potter::Potter(int x_cord, int y_cord, char potter_symbol): Moving(x_cord, y_cord, potter_symbol){  // general constructor of class Potter 

}

vector<int> Potter::moveCharacter(){
    // int curx, cury;
	int ch;
	vector<int> cords;
	// curx = cury = 10;
	// initscr ();
	// printw ("Hello world\n");  
	// refresh ();  // clears the terminal
	// getch ();  // gets the char
	// clear ();  
	do { // waits for a character	
		ch = getch ();
		// move(x, y);  ** first i check then i change (Engine function checks and changes)
		// addch (' ');
		switch (ch){
			case KEY_UP : x--; break;
			case KEY_DOWN : x++; break;
			case KEY_LEFT: y--; break;
			case KEY_RIGHT: y++; break;
		}
		move(x, y);
		addch ('C');
	}while (ch != KEY_UP || ch != KEY_DOWN || ch != KEY_LEFT || ch != KEY_RIGHT || ch != 32);  // Esc ASCII

	cords.push_back(x);
	cords.push_back(y);

	return cords;

}