#include "Moving.h"

Moving::Moving(int x_cord, int y_cord, char any_symbol, Map * map): x(x_cord), y(y_cord), symbol(any_symbol), moving_map(map){
    
}

Moving::~Moving(){

}

int Moving::getX() const{
    return x;
}


int Moving::getY() const{
    return y;
}


void Moving::setX(const int X){
    x = X;
}

void Moving::setY(const int Y){
    y = Y;
}

char Moving::getSymbol() const{
    return symbol;
}