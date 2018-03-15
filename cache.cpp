#include "cache.h"
#include "QHash"
#include "qimage.h"
using namespace std;

Cache::Cache()
{
}

void Cache::clearCache()
{
}

QImage Cache::getLoadedImage()
{
    return image;
}

void Cache::setStartImage(QImage &_image)
{
    image = _image;
}

