#ifndef PROCESSING_H
#define PROCESSING_H

#include <QDebug>
#include <deque>
#include <vector>
#include "imagematrix.h"

class Processing
{
public:
    Processing();
    void median(ImageMatrix &matrix);
    void bilateral(ImageMatrix &matrix, int radius, int sigmaD, int sigmaI);
    void otsu(ImageMatrix &matrix);
    void erosion(ImageMatrix &matrix, int radius);
    void dilatation(ImageMatrix &matrix, int radius);
    void my_filter(ImageMatrix &matrix);
    void my_filter_2(ImageMatrix &matrix);
    void counting(ImageMatrix &matrix, int max_size, QImage &orig);
    void laplace(ImageMatrix &matrix);
    void inverse(ImageMatrix &matrix);
    void histogram(QImage &orig, ImageMatrix &matrix);
};

#endif // PROCESSING_H
