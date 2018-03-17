#ifndef IMAGEMATRIX_H
#define IMAGEMATRIX_H

#include <QImage>

class ImageMatrix
{
private:
    int _cols;
    int _rows;
    int **matrix = nullptr;
public:
    ImageMatrix(int c, int r);
    ImageMatrix(const QImage &src);
    ImageMatrix(ImageMatrix &src);
    void to_image(QImage &img);
    int rows();
    int cols();
    int get(int x,int y);
    void set(int value, int x, int y);
    void scale(int min, int max);
    ~ImageMatrix();
};

#endif // IMAGEMATRIX_H
