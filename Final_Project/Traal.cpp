#include "Traal.h"


Traal::Traal(int x_cord, int y_cord, char traal_symbol, Map * map): Moving(x_cord, y_cord, traal_symbol, map){  // general constructor of class Potter 

}

vector<int> Traal::moveCharacter(){
    int new_x = 0;
    int new_y = 0;
    vector<int> cords;

    int direction = rand() % 4;  // random row

    new_x = x;
    new_y = y;
;
    switch (direction){
        case 0 : new_x--; break;
        case 1 : new_x++; break;
        case 2: new_y--; break;
        case 3: new_y++; break;
    }

    cords.push_back(new_x);
	cords.push_back(new_y);

	return cords;
}