#include "Potter.h"

Potter::Potter(int x_cord, int y_cord, char potter_symbol, Map * map): Moving(x_cord, y_cord, potter_symbol, map){  // general constructor of class Potter 

}

vector<int> Potter::moveCharacter(){
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
			case 27: cords.push_back(-1); cords.push_back(-1); break;    // if the user pressed the Escape button then push back the 'End Game' combination values
			case 32: break;
		}
	}while (ch != KEY_UP && ch != KEY_DOWN && ch != KEY_LEFT && ch != KEY_RIGHT && ch != 32 && ch != 27);

	if (ch == 27){  // return the 'End Game' combination values
		return cords;
    }

	cords.push_back(new_x);
	cords.push_back(new_y);

	return cords;

}
