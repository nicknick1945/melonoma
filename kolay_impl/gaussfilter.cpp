#include "kolya_headers/gaussfilter.h"
#include "qimage.h"
#include "vector"
#include "kolya_headers/utils.h"
#include "qimage.h"
#include "qcolor.h"
using namespace std;
GaussFilter::GaussFilter() {
}

void GaussFilter::doFilter(QImage &image){

    vector<vector<int>> bluredImage = Utils::getEmptyDoubleVector(image.width(),image.height());
    for (int w = 1 ; w < image.width() - 1 ; w++ ){
        for (int h = 1 ; h < image.height() - 1 ; h++){
            double x1 = image.pixelColor(w-1,h-1).blue()*0.5;
            double x2 = image.pixelColor(w,h-1).blue()*0.75;
            double x3 = image.pixelColor(w+1,h-1).blue()*0.5;
            double x4 = image.pixelColor(w-1,h).blue()*0.75;
            double x5 = image.pixelColor(w,h).blue();
            double x6 = image.pixelColor(w+1,h).blue()*0.75;
            double x7 = image.pixelColor(w-1,h+1).blue()*0.5;
            double x8 = image.pixelColor(w,h+1).blue()*0.75;
            double x9 = image.pixelColor(w+1,h+1).blue()*0.5;
            bluredImage[h][w] = (x1+x2+x3+x4+x5+x6+x7+x8+x9)/6;
        }
    }

    for(int w = 0 ; w < image.width() ; w++ ){
        for (int h = 0 ; h < image.height(); h ++){
            int color  = Utils::toCorrectLight(bluredImage.at(h).at(w));
            image.setPixelColor(w,h,QColor(color,color,color,255));
        }
    }

    logger->info("фильтр гаусса успешно завершил работу");

}

QString *GaussFilter::getDescription()
{
    QString *description = new QString("фильтр гаусса для убирания шумов");
    return description;
}

