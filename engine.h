#ifndef ENGINE_H
#define ENGINE_H
#include "qlist.h"
#include "abstractfilter.h"
#include "qstring.h"
#include "loggerfactory.h"
#include "logger.h"
#include "qimage.h"
#include "abstractfilter.h"
#include "mysuperfilter.h"

class Engine{

public:
    Engine();
    QList<AbstractFilter*> *filters = new QList<AbstractFilter*>();
    void doFilter(QImage &image);
    QImage doBinary(QImage image,int treshold,bool isInverse);
    void doFilterPomeh(QImage &image);
    void doSkiletization(QImage &image);
    int culculateCountVolos(QImage &image);
    double culculatePersentVolos(QImage &image);
private:
    LoggerFactory *loggerFactory = new LoggerFactory();
    Logger *logger = loggerFactory->getInstance();
    AbstractFilter *mySuperFilter =  new MySuperFilter();
    int WHITE = 255;
    int BLACK = 0;
};

#endif
