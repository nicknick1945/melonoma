#ifndef DEFAULTWIDGETMODEL_H
#define DEFAULTWIDGETMODEL_H
#include "defaultwidget.h"


class DefaultWidgetModel
{
public:
    DefaultWidgetModel();
    DefaultWidgetModel(DefaultWidget * _widget);
    virtual void show();
    virtual void close();
    virtual void onReturnFromSubProcess();
    void setGeometry(int a, int b ,int c ,int d);
    DefaultWidget *widget;
protected:
    LoggerFactory *loggerFactory = new LoggerFactory();
    Logger *logger = loggerFactory->getInstance();
    CacheFactory *cacheFactory = new CacheFactory();
    Cache *cache = cacheFactory->getInstance();
};

#endif // DEFAULTWIDGETMODEL_H
