#ifndef OTSYBINARIZER_H
#define OTSYBINARIZER_H
#include "abstractfilter.h"
#include "QString"
#include "qimage.h"
#include "vector"

using namespace std;

class OtsyBinarizer : public AbstractFilter
{
public:
    OtsyBinarizer();
    void doFilter(QImage &image);
    QString* getDescription();
private:
   int WHITE  = 0;
   int BLACK  = 255;
   int calculateIntensitySum(vector<int> hist);
   vector<int> calculateHist(QImage &image);
   int INTENSITY_LAYER_NUMBER = 256 ;
   int otsuThreshold(QImage &image);
};

#endif // OTSYBINARIZER_H
