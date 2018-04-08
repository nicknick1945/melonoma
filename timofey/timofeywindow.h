#ifndef TIMOFEYWINDOW_H
#define TIMOFEYWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include "platform_headers/defaultwidget.h"

namespace Ui {
class TimofeyWindow;
}

class TimofeyWindow : public DefaultWidget
{
    Q_OBJECT

public:
    explicit TimofeyWindow(QWidget *parent = 0);
    ~TimofeyWindow();

    void loadSceneIntoGraphicsView(QGraphicsScene*);
    void loadSceneIntoGraphicsView_2(QGraphicsScene*);
    void paramsToLabels(QVector<double>);
    void eraseParams();
    QGraphicsScene *scene;
    QGraphicsScene *scene2;
    QString imagePath;

    QImage defaultImage;
    QImage clusteredImage;
    QImage binaryImage;
    QString* getWidgetName();
private:
    Ui::TimofeyWindow *ui;
    QPixmap makeTransparentImage(QImage&, int);
    QVector<double> calculateFeatures(QImage&);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // TIMOFEYWINDOW_H
