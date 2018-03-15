#include "coords.h"

Coords::Coords(int coordsX , int coordsY ){
    this->cordX = coordsX;
    this->cordY = coordsY;
}

int Coords::getX(){
    return this->cordX;
}

int Coords::getY(){
    return this->cordY;
}

void Coords::setX(int newX)
{
    this->cordX = newX;
}

void Coords::setY(int newY)
{
    this->cordY = newY;
}
