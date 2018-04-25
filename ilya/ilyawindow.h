#ifndef ILYAWINDOW_H
#define ILYAWINDOW_H

#include<QWidget>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QGraphicsScene>
#include <windows.h>
#include "popup.h"
#include "platform_headers/defaultwidget.h"

using namespace cv;

namespace Ui {
class IlyaWindow;
}

class IlyaWindow : public DefaultWidget
{
    Q_OBJECT

public:
    explicit IlyaWindow(QWidget *parent = 0);
    int dilatationKernelSize;
    int dilatationType;
    int kernelSize;
    int xOrder;
    int yOrder;
    int threshold_type;
    int threshold_value;
    QImage grayscale;
    QString filename;
    QImage orImg;
    QImage filteredImage;
    void sobelFilter();
    Mat src,src_gray,dst;
    QImage originalImage;
    QGraphicsScene* scene1 = new QGraphicsScene();
    QGraphicsScene* filteredScene = new QGraphicsScene();
    QImage savedOrImg;
    QString* getWidgetName();




    ~IlyaWindow();

private slots:
    void on_loadButton_clicked();

    void on_sobelButton_clicked();

    void on_kernelSize_valueChanged(int arg1);

    void on_sobelRadioButton_clicked();

    void on_xOrderSlider_sliderMoved(int position);

    void on_yOrderSlider_sliderMoved(int position);

    void on_pushButton_clicked();

    void on_robertsRadioButton_clicked();

    void on_radioButton_clicked();

    void on_saveButton_clicked();

    //void on_radioButton_2_clicked();

    void on_thresholdButton_clicked();

    void on_pushButton_2_clicked();

    void on_thresholdTypeSlider_sliderMoved(int position);

    void on_thresholdValue_sliderMoved(int position);

    void on_dilatationRadioButton_clicked();

    //void on_horizontalSlider_sliderMoved(int position);

    //void on_spinBox_editingFinished();

    //void on_spinBox_valueChanged(int arg1);

    void on_dilatationButton_clicked();

    //void on_dilatationTypeSlider_sliderMoved(int position);

    void on_switchSceneButton_clicked();

    void on_prewittRadioButton_clicked();

    void on_prewittButton_clicked();

    void on_medianRadioButton_clicked();

    void on_medianButton_clicked();

    void on_inpaintButton_clicked();

    void on_billaterialRadioButton_clicked();

    //void on_pushButton_3_clicked();

    void on_billaterialButton_clicked();

    void on_DoGRadioButton_clicked();

    void on_DoGButton_clicked();

    void on_thresholdValue_valueChanged(int value);

    void on_CannySlider_sliderMoved(int position);

    void on_CannyRadioButton_clicked();

private:
    Ui::IlyaWindow *ui;
    PopUp *popUp;
};

#endif // ILYAWINDOW_H
