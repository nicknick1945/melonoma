#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <chrono>
#include "viewer.h"
#include "processing.h"
#include "imagematrix.h"
#include "features.h"
#include "platform_headers/defaultwidget.h"

namespace Ui {
class SashaWindow;
}

class SashaWidget : public DefaultWidget
{
    Q_OBJECT

public:
    explicit SashaWidget(QWidget *parent = 0);
    QString* getWidgetName();
    ~SashaWidget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

    void on_pushButton_6_toggled(bool checked);

    void on_pushButton_6_clicked();

private:
    Ui::SashaWindow *ui;
    QGraphicsScene *scene, *scene_2;
    QImage img, dst, dst_2, dst_3, dst_4;
    QString fileName;
    bool load_flag, proc_flag;
};

#endif // MAINWINDOW_H
