#ifndef DEFAULTWIDGET_H
#define DEFAULTWIDGET_H
#include "qwidget.h"
#include "cache.h"
#include "cachefactory.h"
#include "logger.h"
#include "loggerfactory.h"

class DefaultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DefaultWidget(QWidget *parent = 0);
    virtual QString* getWidgetName()=0;
    void preDestroy();
    void onLoad();
signals:

public slots:
protected:
    LoggerFactory *loggerFactory = new LoggerFactory();
    Logger *logger = loggerFactory->getInstance();
    CacheFactory *cacheFactory = new CacheFactory();
    Cache *cache = cacheFactory->getInstance();

};

#endif // DEFAULTWIDGET_H
