#include "imagematrix.h"

ImageMatrix::ImageMatrix(int c, int r):_cols(c),_rows(r)
{
    matrix = new int* [_rows];
    for (int i=0; i<_rows; ++i)
        matrix[i] = new int [_cols];
}

ImageMatrix::ImageMatrix(const QImage &src):ImageMatrix(src.width(), src.height())
{
    for(int i=0;i<_rows;++i) for(int j=0;j<_cols;++j)
        matrix[i][j] = (src.pixelColor(j,i).red()+src.pixelColor(j,i).green()
                        +src.pixelColor(j,i).blue())/3;
}

ImageMatrix::ImageMatrix(ImageMatrix &src):ImageMatrix(src.cols(), src.rows())
{
    for(int r=0;r<_rows;++r)
        memcpy(matrix[r],src.matrix[r],sizeof(int)*_cols);
}

void ImageMatrix::to_image(QImage &img)
{
    img.scaled(_cols,_rows);
    for(int i=0;i<_rows;++i) for(int j=0;j<_cols;++j)
        img.setPixelColor(j,i,QColor(matrix[i][j],matrix[i][j],matrix[i][j]));
}

int ImageMatrix::rows()
{
    return _rows;
}

int ImageMatrix::cols()
{
    return _cols;
}

int ImageMatrix::get(int x, int y)
{
    if (x>0 && x<_rows && y>0 && y<_cols)
        return matrix[x][y];
    else
        return 0;
}

void ImageMatrix::set(int value, int x, int y)
{
    if (x>0 && x<_rows && y>0 && y<_cols)
        matrix[x][y] = value;
}

void ImageMatrix::scale(int min, int max)
{
    int m_max = matrix[0][0], m_min = matrix[0][0], t;
    for (int i=0; i<_rows; ++i)
        for (int j=0; j<_cols; ++j)
        {
            t = matrix[i][j];
            m_max = std::max(m_max, t);
            m_min = std::min(m_min, t);
        }
    for (int i=0; i<_rows; ++i)
        for (int j=0; j<_cols; ++j)
        {
            t = matrix[i][j];
            matrix[i][j] = ((max-min)*(t-m_min)/(m_max-m_min))+min;
        }
}

ImageMatrix::~ImageMatrix()
{
    for (int r=0;r<_rows;++r)
        delete[] matrix[r];
    delete[] matrix;
}
