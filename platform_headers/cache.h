#ifndef CACHE_H
#define CACHE_H
#include "qhash.h"
#include "qimage.h"

class Cache
{
public:
    Cache();
    void clearCache();
    QImage*  getLoadedImage();
    void setStartImage(QImage *iamge);
    int b;
private:
    QImage *image;
};

#endif // CACHE_H
