#include "contrastfilter.h"
#include "vector"
#include "utils.h"
#include "math.h"
#include "qcolor.h"
using namespace std;
void ContrastFilter::doFilter(QImage &image)
{
    int max = 1 ;
    int multiplexer = 2;
    vector<vector<int>> contrastedWalue = Utils::getEmptyDoubleVector(image.width(), image.height());
    for  (int w = 0 ; w < image.width() ; w ++){
        for (int h = 0 ; h < image.height() ; h ++){
            contrastedWalue.at(h).at(w) = pow((255-image.pixelColor(w,h).blue()),multiplexer);
            if (contrastedWalue.at(h).at(w)>max) max = contrastedWalue.at(h).at(w);
        }
    }

    for  (int w = 0 ; w < image.width() ; w ++){
        for (int h = 0 ; h < image.height() ; h ++){
            int colorValue = 255 - contrastedWalue.at(h).at(w)*255/max;
            colorValue =Utils::toCorrectLight(colorValue);
            image.setPixelColor(w,h,QColor(colorValue,colorValue,colorValue,255));
        }
    }

    logger->debug("фильтр контрастирования применен успешно");
}

QString* ContrastFilter::getDescription()
{
    QString *description = new QString("фильтр увеличения разницы яркостей");
    return description;
}
ContrastFilter::ContrastFilter(): AbstractFilter(){}
