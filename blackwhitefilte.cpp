#include "blackwhitefilte.h"
#include "qimage.h"
#include "abstractfilter.h"
BlackWhiteFilte::BlackWhiteFilte() : AbstractFilter(){}

void BlackWhiteFilte::doFilter(QImage &image){
    int sizeX = image.width();
    int sizeY = image.height();
    for (int x = 0 ; x < sizeX ; x++){
        for (int y = 0 ; y < sizeY ; y++){
            int grey=( image.pixelColor(x,y).red()+image.pixelColor(x,y).blue()+image.pixelColor(x,y).green())/3;
                image.setPixelColor(x,y,QColor(grey,grey,grey,255));
        }
    }
    logger->info("фильтр перевода в оттенки серого применен успешно");
}

QString* BlackWhiteFilte::getDescription()
{
    QString *description = new QString("фильтр для перевода изображения в черно-белые оттенки");
    return description;
}
