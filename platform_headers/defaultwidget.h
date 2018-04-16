#ifndef DEFAULTWIDGET_H
#define DEFAULTWIDGET_H
#include "qwidget.h"
#include "cache.h"
#include "cachefactory.h"
#include "logger.h"
#include "loggerfactory.h"


class MainWindow;

class DefaultWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DefaultWidget(QWidget *parent = 0);
    virtual QString* getWidgetName()=0;
    void preDestroy();
    virtual void onLoad();
    void setMainWindow(MainWindow *mainWindow_);
    void unlockNextButton();
    void lockNextButton();
signals:

protected:
    void nextWidget();
    LoggerFactory *loggerFactory = new LoggerFactory();
    Logger *logger = loggerFactory->getInstance();
    CacheFactory *cacheFactory = new CacheFactory();
    Cache *cache = cacheFactory->getInstance();
private:
    MainWindow *mainWindow;
};


#endif // DEFAULTWIDGET_H
