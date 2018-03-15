#ifndef DIRECTIONVECTOR_H
#define DIRECTIONVECTOR_H

#include "qlist.h"
#include "coords.h"


/**
 * @brief The DirectionVector class
 * этот это модель вектора из которых я буду потом составлять волосы(как втоое пространсво)
 */

class DirectionVector{

public:
    /**
     * @brief DirectionVector
     * @param coords
     */
    DirectionVector(QList<Coords *> &coords);

    /**
     * @brief coords набор координат из которых состоит вектор
     * для начала будем брать за один вектор 5 подряд координат
     */
    QList<Coords*> *coords;
    /**
     * @brief startPoint начало вектора
     */
    Coords *startPoint ;
    /**
     * @brief endPoint конец вектора
     */
    Coords *endPoint;

    /**
     * @brief degreesCount направление вектора в градусах измеряются аналогично часам
     * в интервале от 0-360
     */
    double degreesCount;

    /**
     * @brief imageWidth ширина в пикселах исходного изображения
     */
    int imageWidth ;
    /**
     * @brief imageHeiht высота в пикселах исходного изображения
     */
    int imageHeiht ;



private :
    double calculateDirectionCount();

};

#endif // DIRECTIONVECTOR_H
