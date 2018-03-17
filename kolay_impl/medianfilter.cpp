#include "medianfilter.h"
#include "vector"
#include "kolya_headers/utils.h"

using namespace std;

class MediadMatrx{

public:
    vector<int> filds;
    void goSort(){
        sort(filds.begin(),filds.end());
    }
};

MedianFilter::MedianFilter()
{

}

void MedianFilter::doFilter(QImage &image)
{
       vector<vector<int>> newImageMatrix = Utils::getEmptyDoubleVector(image.width(),image.height());
       for (int h = 0 ; h < image.height(); h ++){
           for (int w = 0 ; w < image.width(); w++){
               MediadMatrx matrix;
               matrix.filds.resize(25);
               for (int i = 0 ; i < 5 ; i ++){
                   for (int j = 0 ; j < 5 ; j ++){
                       int currencyCoordsX = Utils::calculeNormalCoords(w+3-j,image.width());
                       int currencyCoordsY = Utils::calculeNormalCoords(h+3-i,image.height());
                       logger->info(QString::number(j + ( (i+1)*5 ) ) );
                       matrix.filds.at(j+((i)*5)) = image.pixelColor(currencyCoordsX,currencyCoordsY).blue();
                   }
               }
               matrix.goSort();
               newImageMatrix.at(h).at(w) = matrix.filds.at(12);
           }
       }


       for (int h = 0 ; h < image.height(); h ++){
           for (int w = 0 ; w < image.width(); w++){
               int color = newImageMatrix.at(h).at(w);
               image.setPixelColor(w,h,QColor(color,color,color,255));
           }
       }

       logger->info("медианный фильтр успешно применен");
}

QString *MedianFilter::getDescription()
{
    QString *description = new QString("медианный фильтр");
    return description;
}

