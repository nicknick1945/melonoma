#ifndef SAHSAWINDOW_H
#define SAHSAWINDOW_H

#include <QMainWindow>
#include "loggerfactory.h"
#include "logger.h"
#include "cache.h"
#include "cachefactory.h"
#include "defaultwidget.h"
#include "QWidget"
#include "qlist.h"
#include "defaultwidgetmodel.h"
#include "subprocessmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QList<DefaultWidgetModel*> *widgets;
    QHash<QString,DefaultWidgetModel*> *subProcesses;
    void returnToProcess();
    QWidget *currentForm ;
    void lockNextNutton();
    void unlockNextButton();
    ~MainWindow();
    void goToSubProcess(QString subProcessName);
    void returnFromSubProcess();
    void next();

private slots:
    void on_nextButton_clicked();
    void on_previous_clicked();
    void on_LoadPhotoButton_clicked();


private:
    QString * currentSubProcessName;
    LoggerFactory *loggerFactory = new LoggerFactory();
    Logger *logger = loggerFactory->getInstance();
    CacheFactory *cacheFactory = new CacheFactory();
    Cache *cache = cacheFactory->getInstance();
    void addWidgets();
    void setWidgetsGeometry(DefaultWidgetModel &widget);
    int currentWidgetNumber = 0;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
