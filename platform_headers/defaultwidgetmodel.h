#ifndef DEFAULTWIDGETMODEL_H
#define DEFAULTWIDGETMODEL_H
#include "defaultwidget.h"


class DefaultWidgetModel
{
public:
    DefaultWidgetModel();
    DefaultWidgetModel(DefaultWidget * _widget);
    void show();
    void close();
    void setGeometry(int a, int b ,int c ,int d);
    DefaultWidget *widget;
private :
    LoggerFactory *loggerFactory = new LoggerFactory();
    Logger *logger = loggerFactory->getInstance();
    CacheFactory *cacheFactory = new CacheFactory();
    Cache *cache = cacheFactory->getInstance();
};

#endif // DEFAULTWIDGETMODEL_H
