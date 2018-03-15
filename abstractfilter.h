#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H
#include "qimage.h"
#include "loggerfactory.h"
#include "logger.h"

class AbstractFilter
{
public:
    AbstractFilter();
    virtual void doFilter(QImage &image) = 0;
    virtual QString* getDescription() = 0;
    LoggerFactory *loggerFactory = new LoggerFactory();
    Logger *logger = loggerFactory->getInstance();

protected :

};

#endif // ABSTRACTFILTER_H
