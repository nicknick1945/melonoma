#ifndef FEATURES_H
#define FEATURES_H

#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "imagematrix.h"

class Features
{
private:
    int minR;
    int meanR;
    int maxR;
    int minG;
    int meanG;
    int maxG;
    int minB;
    int meanB;
    int maxB;
    int minTh;
    int meanTh;
    int maxTh;
    //void calculateFeatures(QImage &orig, ImageMatrix &mask, int counter);
    void saveFeatures(QString &fileName, int x, int y);
    void calculateColors(int x, int y, int &count, QImage &orig);
    //void calculateThickness();

public:
    Features(/*QImage &orig, ImageMatrix &mask*/);
    int getMinR() {return minR;}
    int getMeanR() {return meanR;}
    int getMaxR() {return maxR;}
    int getMinG() {return minG;}
    int getMeanG() {return meanG;}
    int getMaxG() {return maxG;}
    int getMinB() {return minB;}
    int getMeanB() {return meanB;}
    int getMaxB() {return maxB;}
    int getMinTh() {return minTh;}
    int getMeanTh() {return meanTh;}
    int getMaxTh() {return maxTh;}
    void calculateFeatures(QImage &orig, ImageMatrix &mask, QString &fileName);
};

#endif // FEATURES_H
