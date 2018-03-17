#ifndef COORDS_H
#define COORDS_H


class Coords
{

public :
     Coords(int coordsX , int coordsY);
     int getX();
     int getY();
     void setX(int newX);
     void setY(int newY);
private :
     int cordX;
     int cordY;

};

#endif // COORDS_H
