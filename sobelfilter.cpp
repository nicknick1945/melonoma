#include "sobelfilter.h"
#include "utils.h"
#include "vector"
#include "qcolor.h"
using namespace std;

SobelFilter::SobelFilter()
{

}

void SobelFilter::doFilter(QImage &image)
{
    vector<vector<int>> vertivalSobelMatrix = Utils::getEmptyDoubleVector(3,3);
    vector<vector<int>> horizontalSobelMatrix = Utils::getEmptyDoubleVector(3,3);
    vertivalSobelMatrix.at(0).at(0) = -1;
    vertivalSobelMatrix.at(0).at(1) = -1;
    vertivalSobelMatrix.at(0).at(2) = -1;
    vertivalSobelMatrix.at(1).at(0) = 0;
    vertivalSobelMatrix.at(1).at(1) = 0;
    vertivalSobelMatrix.at(1).at(2) = 0;
    vertivalSobelMatrix.at(2).at(0) = 1;
    vertivalSobelMatrix.at(2).at(1) = 1;
    vertivalSobelMatrix.at(2).at(2) = 1;

    horizontalSobelMatrix.at(0).at(0) = -1;
    horizontalSobelMatrix.at(0).at(1) = 0;
    horizontalSobelMatrix.at(0).at(2) = 1;
    horizontalSobelMatrix.at(1).at(0) = -1;
    horizontalSobelMatrix.at(1).at(1) = 0;
    horizontalSobelMatrix.at(1).at(2) = 1;
    horizontalSobelMatrix.at(2).at(0) = -1;
    horizontalSobelMatrix.at(2).at(1) = 0;
    horizontalSobelMatrix.at(2).at(2) = 1;

    vector<vector<int>> newColorsMatrixR = Utils::getEmptyDoubleVector(image.width(),image.height());
    vector<vector<int>> newColorsMatrixG = Utils::getEmptyDoubleVector(image.width(),image.height());
    vector<vector<int>> newColorsMatrixB = Utils::getEmptyDoubleVector(image.width(),image.height());

    for (int w = 0 ; w < image.width() ;w ++){
        for(int h = 0 ; h < image.height(); h++) {
            double sumXR = 0;
            double sumYR = 0;
            double sumXG = 0;
            double sumYG = 0;
            double sumXB = 0;
            double sumYB = 0;
            for (int i = 0 ; i < 3 ; i ++ ){
                for (int j = 0 ; j < 3 ; j++){
                    int currencyCoordsX =Utils::calculeNormalCoords( w-i+1,image.width()-1);
                    int currenceCoordsY =Utils::calculeNormalCoords( h-j+1,image.height()-1);
                    sumXR = sumXR + image.pixelColor(currencyCoordsX,currenceCoordsY).red()*horizontalSobelMatrix.at(i).at(j);
                    sumXR = sumXR + image.pixelColor(currencyCoordsX,currenceCoordsY).red()*horizontalSobelMatrix.at(i).at(j);
                    sumXG = sumXG + image.pixelColor(currencyCoordsX,currenceCoordsY).green()*horizontalSobelMatrix.at(i).at(j);
                    sumXG = sumXG + image.pixelColor(currencyCoordsX,currenceCoordsY).green()*horizontalSobelMatrix.at(i).at(j);
                    sumXB = sumXB + image.pixelColor(currencyCoordsX,currenceCoordsY).blue()*horizontalSobelMatrix.at(i).at(j);
                    sumXB = sumXB + image.pixelColor(currencyCoordsX,currenceCoordsY).blue()*horizontalSobelMatrix.at(i).at(j);

                }
            }
            newColorsMatrixR.at(h).at(w) = Utils::toCorrectLight(calculeateTargetValue(sumXR,sumYR));
            newColorsMatrixG.at(h).at(w) = Utils::toCorrectLight(calculeateTargetValue(sumXG,sumYG));
            newColorsMatrixB.at(h).at(w) = Utils::toCorrectLight(calculeateTargetValue(sumXB,sumYB));
        }
    }
    logger->debug("успешно рассчитали новые коффициенты для изоббражения с помошью оператора собеля");

    for (int w = 0 ; w < image.width() ; w++){
        for (int h = 0 ; h <image.height() ; h++){
            int colorR = newColorsMatrixR.at(h).at(w);
            int colorG = newColorsMatrixG.at(h).at(w);
            int colorB = newColorsMatrixB.at(h).at(w);
            image.setPixelColor(w,h,QColor(colorR,colorG,colorB,255));
        }
    }

    logger->debug("успешно применили оператор собеля");

}



QString *SobelFilter::getDescription()
{
    QString *description = new QString("фильтр собеля для нахождения границ");
    return description;
}

double SobelFilter::calculeateTargetValue(double xValue, double yValue)
{
    return sqrt(pow(xValue,2) + pow(yValue,2));
}


