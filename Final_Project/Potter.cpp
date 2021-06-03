#include "Potter.h"

#include <stdlib.h>


Potter::Potter(int x_cord, int y_cord, char potter_symbol): Moving(x_cord, y_cord, potter_symbol){  // general constructor of class Potter 

}

vector<int> Potter::moveCharacter(){
    // int curx, cury;
	int ch;
	vector<int> cords;
	  
	int new_x = 0;
	int new_y = 0;

	do { 
		new_x = x;
		new_y = y;

		ch = getch ();
		switch (ch){
			case KEY_UP : new_x--; break;
			case KEY_DOWN : new_x++; break;
			case KEY_LEFT: new_y--; break;
			case KEY_RIGHT: new_y++; break;
		}
	}while (ch != KEY_UP && ch != KEY_DOWN && ch != KEY_LEFT && ch != KEY_RIGHT && ch!= 32);

	// printw("HELLO@");
	cords.push_back(new_x);
	cords.push_back(new_y);

	return cords;

}