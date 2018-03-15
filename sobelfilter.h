#ifndef SOBELFILTER_H
#define SOBELFILTER_H
#include "abstractfilter.h"
#include "vector"
#include "qimage.h"
#include "math.h"
using namespace std;
class SobelFilter : public AbstractFilter
{
public:
    SobelFilter();
    void doFilter(QImage &image);
    QString* getDescription();
 private:
    /**
     * @brief calculeNormalCoords функция позволит избежать выхода за рамки изображения
     * @param value координата
     * @param maxCoodrs максимально возможная для изображения координата
     * @return
     */
    int calculeNormalCoords(int value,int maxCoodrs);

    /**
     * @brief calculeateTargetValue считает корень из суммы квадратов
     * @param xValue
     * @param yValye
     * @return
     */
    double calculeateTargetValue(double xValue , double yValue);
};

#endif // SOBELFILTER_H
