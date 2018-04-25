#ifndef ALEXWINDOW_H
#define ALEXWINDOW_H
#include <QListWidgetItem>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <QDir>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include "platform_headers/defaultwidget.h"

namespace Ui {
class AlexWindow;
}

class AlexWindow : public DefaultWidget
{
    Q_OBJECT

public:
    explicit AlexWindow(QWidget *parent = 0);
    ~AlexWindow();

    double getMaxOnVector(QVector<double> vec,int size);
    double getMidOnVector(QVector<double> vec,int size);
    double getSKOOnVector(QVector<double> vec,int size, double mid);
    void createGist(QImage image);
    int getMin(QVector<double> vec,int size);
    int getMax(QVector<double> vec,int size);
    int getMid(int min, int max);
    int getSko(int min, int max, int mid);
    QString* getWidgetName();

private slots:

    void canny();

    void smooth();

    void sobelqt();

    void erode_dilate();

    void filter_matrix();

    void sobel();

    void laplace();

    void on_pushButton_canny_clicked();

    void on_pushButton_sobel_clicked();

    void on_pushButton_contours_clicked();

    void on_path_itemClicked(QListWidgetItem *item);

    void on_pushButton_smooth_clicked();

    void on_pushButton_laplace_clicked();

    void on_pushButton_erode_dilate_clicked();

    void on_pushButton_filter_matrix_clicked();

    void on_pushButton_sobelqt_clicked();

    void showMessage();

    void open_image();

    void open_image_window();

    void show_guide();

    void convert_Mat2QImage();

    void convert_QImage2Mat();

    void on_horizontalSlider_valueChanged();

    void save_image();

    void quit();

    void temp();

    void on_pushButton_magic_clicked();

private:
    Ui::AlexWindow *ui;
    IplImage* image;
    IplImage* image_draw;
    QGraphicsScene* S_img  = nullptr;
    QImage img;
    QImage tmp;
    int maXX;
    int minX, maxX, minY, maxY;

    int value1,value2;
};

#endif // ALEXWINDOW_H
