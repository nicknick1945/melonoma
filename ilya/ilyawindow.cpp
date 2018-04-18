#include "ui_ilyawindow.h"
#include "ilyawindow.h"
#include <QErrorMessage>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QFileDialog>
#include <QWheelEvent>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "algorithms.h"
#include "dilatation.h"
#include <QWheelEvent>
#include <ilya/opencvtransform.h>
#include <opencv2/photo/photo.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <QPainter>
#include <QRect>

using namespace cv;

IlyaWindow::IlyaWindow(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::IlyaWindow)
{


    ui->setupUi(this);
    popUp = new PopUp();
    IlyaWindow::setWindowTitle("Программа выделения");
    kernelSize=3;
    xOrder=0;
    yOrder=0;
    dilatationKernelSize=1;
    dilatationType=0;
    ui->sobelButton->hide();
    ui->medianButton->hide();
    ui->kernelSize->hide();
    ui->kernelSizeTitle->hide();
    ui->xOrderSlider->hide();
    ui->yOrderSlider->hide();
    ui->zeroXOrderLabel->hide();
    ui->zeroYOrderLabel->hide();
    ui->oneXOrderLabel->hide();
    ui->oneYOrderLabel->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->thresholdTypeSlider->hide();
    ui->thresholdTypeLabel->hide();
    ui->thresholdValue->hide();
    ui->dilatationButton->hide();
    ui->dilatationKernelSizeSpinBox->hide();
    ui->dilatationTypeSlider->hide();
    ui->xLabel->hide();
    ui->yLabel->hide();
    ui->dilatationTypeLabel->hide();
    threshold_type=0;
    threshold_value=0;
    dilatationType=0;
    dilatationKernelSize=1;
    ui->prewittButton->hide();
    ui->billaterialButton->hide();
    ui->label->hide();
    ui->thresholdValueDisplay->hide();
    ui->DoGButton->hide();
    ui->sigmasLineEdit->hide();
    ui->firstSigmaSpinBox->hide();
    ui->secondSigmaSpinBox->hide();
    ui->CannySlider->hide();




}

IlyaWindow::~IlyaWindow()
{
    delete ui;
}



// Loading image. Path is in filename and original image is in orImg
void IlyaWindow::on_loadButton_clicked()
{

    filename=QFileDialog::getOpenFileName();
    orImg.load(filename);
    savedOrImg=orImg;
    std::string file=filename.toUtf8().constData();
    src=imread(file);
    QGraphicsScene* scene = new QGraphicsScene();
    ui->originalImage->setScene(scene);
    scene->addPixmap(QPixmap::fromImage(orImg));
    ui->originalImage->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->originalImage->update();
    popUp->setPopupText("Изображение загружено");
    popUp->show();

}
void IlyaWindow::sobelFilter()
{

    Mat grad;
    int scale=1;
    int delta=0;
    int ddepth=CV_16S;

    //int c;
    //const std::string file=filename.toStdString();
    //orImg.convertToFormat(QImage::Format_RGB888);
    /*
    std::string file=filename.toUtf8().constData();
    src=imread(file);
    */

    GaussianBlur(src,src,Size(3,3),0,0,BORDER_DEFAULT);
    cvtColor(src,src_gray,CV_BGR2GRAY);
    Mat grad_x,grad_y;
    Mat abs_grad_x,abs_grad_y;

    //Gradient on x component
    Sobel(src,grad_x,ddepth,xOrder,yOrder,kernelSize,scale,delta,BORDER_DEFAULT);
    convertScaleAbs(grad_x,abs_grad_x);

    //Gradient on y component
    Sobel(src,grad_y,ddepth,xOrder,yOrder,kernelSize,scale,delta,BORDER_DEFAULT);
    convertScaleAbs(grad_y,abs_grad_y);

    addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,grad);
    //imwrite("x.jpg",grad);
    //QImage filteredImage("x.jpg");
    //cvtColor(grad,grad,CV_BGR2RGB);
    //filteredImage((uchar*)grad.data,grad.cols,grad.rows,QImage::Format_RGB32);



    //imwrite("C://Users/llya/Desktop/index.jpg",grad);
    //filteredImage.load("C://Users/llya/Desktop/index.jpg");
    //filteredImage=Mat2QImage(grad);
    filteredImage=ASM::cvMatToQImage(grad);



    //QGraphicsScene* scene = new QGraphicsScene();
    ui->filteredScene->setScene(scene1);
    scene1->addPixmap(QPixmap::fromImage(filteredImage));
    ui->filteredScene->fitInView(scene1->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();
    popUp->setPopupText("Обработка изображения прошла успешно");
    popUp->show();
}

void IlyaWindow::on_sobelButton_clicked()
{
    if(xOrder==0 && yOrder==0)
    {
        QErrorMessage msg;

        msg.setWindowTitle("Ошибка");
        msg.showMessage("Хотя бы одна производная не должная равняться нулю");
        msg.show();
        msg.exec();
    }
    else
    {
        sobelFilter();
        popUp->setPopupText("Обработка изображения прошла успешно");
        popUp->show();
    }

}

void IlyaWindow::on_kernelSize_valueChanged(int arg1)
{
    kernelSize=arg1;
}

void IlyaWindow::on_sobelRadioButton_clicked()
{
    kernelSize=3;
    ui->pushButton->hide();
    ui->kernelSize->show();
    ui->kernelSizeTitle->show();
    ui->sobelButton->show();
    ui->xOrderSlider->show();
    ui->yOrderSlider->show();
    ui->zeroXOrderLabel->show();
    ui->zeroYOrderLabel->show();
    ui->oneXOrderLabel->show();
    ui->oneYOrderLabel->show();
    ui->pushButton_2->hide();
    ui->thresholdTypeSlider->hide();
    ui->thresholdTypeLabel->hide();
    ui->thresholdValue->hide();
    ui->dilatationButton->hide();
    ui->dilatationKernelSizeSpinBox->hide();
    ui->dilatationTypeSlider->hide();
    ui->xLabel->show();
    ui->yLabel->show();
    ui->medianButton->hide();
    ui->prewittButton->hide();
    ui->label->hide();
    ui->thresholdValueDisplay->hide();
    ui->DoGButton->hide();
    ui->sigmasLineEdit->hide();
    ui->firstSigmaSpinBox->hide();
    ui->secondSigmaSpinBox->hide();
    ui->CannySlider->hide();

}

void IlyaWindow::on_xOrderSlider_sliderMoved(int position)
{
    if(position>0)
    {
        ui->yOrderSlider->hide();
        yOrder=0;
    }
    if(position==0)
    {
        ui->yOrderSlider->show();
    }
    xOrder=position;
}

void IlyaWindow::on_yOrderSlider_sliderMoved(int position)
{
    if(position>0)
    {
        ui->xOrderSlider->hide();
        xOrder=0;
    }
    if(position==0)
    {
        ui->xOrderSlider->show();
    }
    yOrder=position;
}

void IlyaWindow::on_pushButton_clicked()
{
    //QGraphicsScene* scene=new QGraphicsScene();

    ui->filteredScene->setScene(scene1);
    QImage res;
    res=orImg.convertToFormat(QImage::Format_Grayscale8);
    res=roberts(res);
    filteredImage=res;


    scene1->addPixmap(QPixmap::fromImage(res));
    //res.save("test.jpg");
    ui->filteredScene->fitInView(scene1->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();
    popUp->setPopupText("Обработка изображения прошла успешно");
    popUp->show();

}

void IlyaWindow::on_robertsRadioButton_clicked()
{
    ui->sobelButton->hide();
    ui->kernelSize->hide();
    ui->kernelSizeTitle->hide();
    ui->xOrderSlider->hide();
    ui->yOrderSlider->hide();
    ui->zeroXOrderLabel->hide();
    ui->zeroYOrderLabel->hide();
    ui->oneXOrderLabel->hide();
    ui->oneYOrderLabel->hide();
    ui->pushButton->show();
    ui->pushButton_2->hide();
    ui->thresholdTypeSlider->hide();
    ui->thresholdTypeLabel->hide();
    ui->thresholdValue->hide();
    ui->dilatationButton->hide();
    ui->dilatationKernelSizeSpinBox->hide();
    ui->dilatationTypeSlider->hide();
    ui->xLabel->hide();
    ui->yLabel->hide();
    ui->prewittButton->hide();
    ui->medianButton->hide();
    ui->CannySlider->hide();
    ui->billaterialButton->hide();
    ui->label->hide();
    ui->thresholdValueDisplay->hide();
    ui->DoGButton->hide();
    ui->sigmasLineEdit->hide();
    ui->firstSigmaSpinBox->hide();
    ui->secondSigmaSpinBox->hide();

}












void IlyaWindow::on_radioButton_clicked()
{
    kernelSize=CV_SCHARR;
    ui->pushButton->hide();
    ui->kernelSize->hide();
    ui->kernelSizeTitle->hide();
    ui->sobelButton->show();
    ui->xOrderSlider->show();
    ui->yOrderSlider->show();
    ui->zeroXOrderLabel->show();
    ui->zeroYOrderLabel->show();
    ui->oneXOrderLabel->show();
    ui->oneYOrderLabel->show();
    ui->pushButton_2->hide();
    ui->thresholdTypeSlider->hide();
    ui->thresholdValue->hide();
    ui->dilatationButton->hide();
    ui->CannySlider->hide();
    ui->dilatationKernelSizeSpinBox->hide();
    ui->dilatationTypeSlider->hide();
    ui->dilatationButton->hide();
    ui->dilatationKernelSizeSpinBox->hide();
    ui->dilatationTypeSlider->hide();
    ui->xLabel->show();
    ui->yLabel->show();
    ui->prewittButton->hide();
    ui->medianButton->hide();
    ui->billaterialButton->hide();
    ui->label->hide();
    ui->thresholdValueDisplay->hide();
    ui->DoGButton->hide();
    ui->sigmasLineEdit->hide();
    ui->firstSigmaSpinBox->hide();
    ui->secondSigmaSpinBox->hide();



}



void IlyaWindow::on_saveButton_clicked()
{
    //filteredImage.save(QFileDialog::getSaveFileName());
    QString imagepath=QFileDialog::getSaveFileName(this,tr("Save File"),"",tr("JPEG(*.jpg *.jpeg);;PNG(*.png)"));
    bool save = filteredImage.save(imagepath);
    if(save){
        popUp->setPopupText("Изображение было успешно сохранено");
        popUp->show();
    }
}


void IlyaWindow::on_thresholdButton_clicked()
{
    ui->sobelButton->hide();
    ui->kernelSize->hide();
    ui->kernelSizeTitle->hide();
    ui->xOrderSlider->hide();
    ui->CannySlider->hide();
    ui->yOrderSlider->hide();
    ui->zeroXOrderLabel->hide();
    ui->zeroYOrderLabel->hide();
    ui->oneXOrderLabel->hide();
    ui->oneYOrderLabel->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_2->show();
    ui->thresholdTypeSlider->show();
    ui->thresholdTypeLabel->show();
    ui->thresholdValue->show();
    ui->dilatationButton->hide();
    ui->dilatationKernelSizeSpinBox->hide();
    ui->dilatationTypeSlider->hide();
    ui->xLabel->hide();
    ui->yLabel->hide();
    ui->medianButton->hide();
    ui->billaterialButton->hide();
    ui->thresholdValueDisplay->show();
    ui->DoGButton->hide();
    ui->sigmasLineEdit->hide();
    ui->firstSigmaSpinBox->hide();
    ui->secondSigmaSpinBox->hide();






}

void IlyaWindow::on_pushButton_2_clicked()
{
    /*Mat src, src_gray, dst;
    std::string file=filename.toUtf8().constData();
    src=imread(file);

    //int threshold_value = 180;
    //int threshold_type = 3;;
   // int const max_value = 255;
    //int const max_type = 4;
    int const max_BINARY_value = 255;

    cvtColor(src,src_gray,CV_BGR2GRAY);
    threshold(src_gray,dst,threshold_value,max_BINARY_value,threshold_type);
    imwrite("/home/s-n-a/x.jpg",dst);
    filteredImage.load("/home/s-n-a/x.jpg");
    QGraphicsScene* scene = new QGraphicsScene();
    ui->filteredScene->setScene(scene);
    scene->addPixmap(QPixmap::fromImage(filteredImage));
    ui->filteredScene->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();
*/
}

void IlyaWindow::on_thresholdTypeSlider_sliderMoved(int position)
{
    threshold_type=position;


}

void IlyaWindow::on_thresholdValue_sliderMoved(int position)
{
    threshold_value=position;
    QString s=QString::number(position);
    ui->thresholdValueDisplay->setText(s);


    //int threshold_value = 180;
    //int threshold_type = 3;;
   // int const max_value = 255;
    //int const max_type = 4;
    int const max_BINARY_value = 255;

    cvtColor(src,src_gray,CV_BGR2GRAY);
    threshold(src_gray,dst,threshold_value,max_BINARY_value,threshold_type);
    //imwrite("C://Users/llya/Desktop/index.jpg",dst);
    filteredImage=ASM::cvMatToQImage(dst);
    //filteredImage.load("C://Users/llya/Desktop/index.jpg");
    scene1->clear();
    ui->filteredScene->setScene(scene1);
    scene1->addPixmap(QPixmap::fromImage(filteredImage));

    ui->filteredScene->fitInView(scene1->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();


}




void IlyaWindow::on_dilatationRadioButton_clicked()
{
    ui->sobelButton->hide();
    ui->kernelSize->hide();
    ui->kernelSizeTitle->hide();
    ui->xOrderSlider->hide();
    ui->yOrderSlider->hide();
    ui->zeroXOrderLabel->hide();
    ui->zeroYOrderLabel->hide();
    ui->oneXOrderLabel->hide();
    ui->oneYOrderLabel->hide();
    ui->pushButton->hide();
    ui->CannySlider->hide();
    ui->pushButton_2->hide();
    ui->thresholdTypeSlider->hide();
    ui->thresholdTypeLabel->hide();
    ui->thresholdValue->hide();
    ui->dilatationButton->show();
    ui->dilatationKernelSizeSpinBox->show();
    ui->label->show();
    ui->thresholdValueDisplay->hide();
    ui->dilatationTypeSlider->show();
    ui->xLabel->hide();
    ui->dilatationTypeLabel->show();
    ui->yLabel->hide();
    ui->prewittButton->hide();
    ui->medianButton->hide();
    ui->billaterialButton->hide();
    ui->label->show();
    ui->thresholdValueDisplay->hide();
    ui->DoGButton->hide();
    ui->sigmasLineEdit->hide();
    ui->firstSigmaSpinBox->hide();
    ui->secondSigmaSpinBox->hide();



}







void IlyaWindow::on_dilatationButton_clicked()
{
    dilatationType=ui->dilatationTypeSlider->value();
    dilatationKernelSize=ui->dilatationKernelSizeSpinBox->value();
    dst=dilatationOperator(orImg,dilatationType,dilatationKernelSize);
    //QImage img;
    //img.load("C://Users/llya/Desktop/index.jpg");
    filteredImage=ASM::cvMatToQImage(dst);
    QGraphicsScene* scene = new QGraphicsScene();
    ui->filteredScene->setScene(scene);
    scene->addPixmap(QPixmap::fromImage(filteredImage));
    ui->filteredScene->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();
    popUp->setPopupText("Обработка изображения прошла успешно");
    popUp->show();
}


void IlyaWindow::on_switchSceneButton_clicked()
{
    QImage tmp;
    tmp=orImg;
    orImg=filteredImage;
    orImg=orImg.convertToFormat(QImage::Format_RGB32);
    filteredImage=tmp;
    src=ASM::QImageToCvMat(orImg);

    QGraphicsScene *scene1=new QGraphicsScene();
    QGraphicsScene *scene2=new QGraphicsScene();
    ui->originalImage->setScene(scene1);
    ui->filteredScene->setScene(scene2);
    scene1->addPixmap(QPixmap::fromImage(orImg));
    scene2->addPixmap(QPixmap::fromImage(filteredImage));
    ui->originalImage->fitInView(scene1->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->originalImage->update();
    ui->filteredScene->fitInView(scene2->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();
}



void IlyaWindow::on_prewittRadioButton_clicked()
{
    ui->pushButton->hide();
    ui->sobelButton->hide();
    ui->kernelSize->hide();
    ui->kernelSizeTitle->hide();
    ui->sobelButton->show();
    ui->xOrderSlider->show();
    ui->yOrderSlider->show();
    ui->zeroXOrderLabel->show();
    ui->zeroYOrderLabel->show();
    ui->oneXOrderLabel->show();
    ui->oneYOrderLabel->show();
    ui->CannySlider->hide();
    ui->pushButton_2->hide();
    ui->thresholdTypeSlider->hide();
    ui->thresholdValue->hide();
    ui->dilatationButton->hide();
    ui->dilatationKernelSizeSpinBox->hide();
    ui->dilatationTypeSlider->hide();
    ui->dilatationButton->hide();
    ui->dilatationKernelSizeSpinBox->hide();
    ui->dilatationTypeSlider->hide();
    ui->xLabel->hide();
    ui->prewittButton->show();
    ui->yLabel->hide();
    ui->medianButton->hide();
    ui->billaterialButton->hide();
    ui->label->hide();
    ui->thresholdValueDisplay->hide();
    ui->xLabel->hide();
    ui->xOrderSlider->hide();
    ui->yLabel->hide();
    ui->yOrderSlider->hide();
    ui->dilatationTypeLabel->hide();
    ui->zeroXOrderLabel->hide();
    ui->zeroYOrderLabel->hide();
    ui->oneXOrderLabel->hide();
    ui->oneYOrderLabel->hide();
    ui->DoGButton->hide();
    ui->sigmasLineEdit->hide();
    ui->firstSigmaSpinBox->hide();
    ui->secondSigmaSpinBox->hide();


}

void IlyaWindow::on_prewittButton_clicked()
{
    QImage tmp;
    tmp=orImg.convertToFormat(QImage::Format_Grayscale8);
    tmp=prewitt(tmp);
    filteredImage=tmp;
    QGraphicsScene* scene = new QGraphicsScene();
    ui->filteredScene->setScene(scene);
    scene->addPixmap(QPixmap::fromImage(filteredImage));
    ui->filteredScene->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();
    popUp->setPopupText("Обработка изображения прошла успешно");
    popUp->show();

}


void IlyaWindow::on_medianRadioButton_clicked()
{
    kernelSize=3;
    ui->sobelButton->hide();
    ui->kernelSize->show();
    ui->kernelSizeTitle->show();
    ui->xOrderSlider->hide();
    ui->yOrderSlider->hide();
    ui->zeroXOrderLabel->hide();
    ui->CannySlider->hide();
    ui->zeroYOrderLabel->hide();
    ui->oneXOrderLabel->hide();
    ui->oneYOrderLabel->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->thresholdTypeSlider->hide();
    ui->thresholdTypeLabel->hide();
    ui->thresholdValue->hide();
    ui->dilatationButton->hide();
    ui->dilatationKernelSizeSpinBox->hide();
    ui->dilatationTypeSlider->hide();
    ui->xLabel->hide();
    ui->yLabel->hide();
    ui->dilatationTypeLabel->hide();
    threshold_type=0;
    threshold_value=0;
    dilatationType=0;
    dilatationKernelSize=1;
    ui->prewittButton->hide();
    ui->medianButton->show();
    ui->billaterialButton->hide();
    ui->label->hide();
    ui->thresholdValueDisplay->hide();
    ui->DoGButton->hide();
    ui->sigmasLineEdit->hide();
    ui->firstSigmaSpinBox->hide();
    ui->secondSigmaSpinBox->hide();

}

void IlyaWindow::on_medianButton_clicked()
{

    src.convertTo(src,CV_8UC3);
    medianBlur(src,dst,kernelSize);
    //imwrite("C://Users/llya/Desktop/index.jpg",dst);
    //filteredImage.load("C://Users/llya/Desktop/index.jpg");
    filteredImage=ASM::cvMatToQImage(dst);
    scene1->clear();
    ui->filteredScene->setScene(scene1);
    scene1->addPixmap(QPixmap::fromImage(filteredImage));

    ui->filteredScene->fitInView(scene1->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();
    popUp->setPopupText("Обработка изображения прошла успешно");
    popUp->show();
}



void IlyaWindow::on_inpaintButton_clicked()
{   /*
    Mat tmp,res;
    filename=QFileDialog::getOpenFileName();
    std::string file=filename.toUtf8().constData();
    tmp=imread(file);
    bitwise_xor(dst,tmp,res);
    imwrite(file,res);
    QImage tmp;
    tmp=savedOrImg;
    QColor c(255,0,255);
    //tmp.load(QFileDialog::getOpenFileName());
    //filteredImage=ASM::cvMatToQImage(dst);
    for( int i = 0; i < filteredImage.rect().right(); i++ ) {
    for( int j = 0; j < filteredImage.rect().bottom(); j++ ) {

    int br = qGray(filteredImage.pixel(i,j));


    if (br==255)
    {
    tmp.setPixel(i,j,c.rgba());
    //orImg.setPixel(i,j,0);
    //orImg.setPixel(i,j,0);
    }
    }
    }
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(tmp));
    ui->filteredScene->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();
    filteredImage=tmp;
    */



    //dst=ASM::QImageToCvMat(filteredImage);
    //Mat svdorimg;
    //svdorimg=ASM::QImageToCvMat(savedOrImg);
    //Mat res;

    /*
     *
     * Working part
    savedOrImg.save(filename);
    std::string file=filename.toUtf8().constData();
    src=imread(file);
    QString maskname=QFileDialog::getOpenFileName();
    std::string newfile=maskname.toUtf8().constData();
    dst=imread(newfile);
    //src=imread("C:\\Users\\Ilya\\Desktop\\1.jpg");



    int i =dst.type();
    cvtColor(dst,dst,CV_BGR2GRAY);
    i=dst.type();
    printf("%d",i);
    src.convertTo(src,CV_8UC1);
    printf("%d",src.type());

    inpaint(src,dst,dst,20,INPAINT_TELEA);
    imwrite(file,dst);

    */




}

void IlyaWindow::on_billaterialRadioButton_clicked()
{
    kernelSize=1;
    ui->sobelButton->hide();
    ui->medianButton->hide();
    ui->kernelSize->hide();
    ui->kernelSizeTitle->hide();
    ui->billaterialButton->show();
    ui->xOrderSlider->hide();
    ui->yOrderSlider->hide();
    ui->zeroXOrderLabel->hide();
    ui->zeroYOrderLabel->hide();
    ui->oneXOrderLabel->hide();
    ui->oneYOrderLabel->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->CannySlider->hide();
    ui->thresholdTypeSlider->hide();
    ui->thresholdTypeLabel->hide();
    ui->thresholdValue->hide();
    ui->dilatationButton->hide();
    ui->dilatationKernelSizeSpinBox->show();
    ui->dilatationTypeSlider->hide();
    ui->xLabel->hide();
    ui->yLabel->hide();
    ui->dilatationTypeLabel->hide();
    ui->prewittButton->hide();
    ui->label->show();
    ui->thresholdValueDisplay->hide();
    ui->DoGButton->hide();
    ui->sigmasLineEdit->hide();
    ui->firstSigmaSpinBox->hide();
    ui->secondSigmaSpinBox->hide();

}



void IlyaWindow::on_billaterialButton_clicked()
{
    src.convertTo(src,CV_8UC3);
    int tmp;
    tmp=ui->dilatationKernelSizeSpinBox->value();
    //adaptiveThreshold(src,dst,128,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,3,5);
    bilateralFilter(src,dst,15,200,200);
    filteredImage=ASM::cvMatToQImage(dst);
    scene1->clear();
    ui->filteredScene->setScene(scene1);
    scene1->addPixmap(QPixmap::fromImage(filteredImage));

    ui->filteredScene->fitInView(scene1->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();
    filteredImage.convertToFormat(QImage::Format_RGB32);
    popUp->setPopupText("Обработка изображения прошла успешно");
    popUp->show();

}

void IlyaWindow::on_DoGRadioButton_clicked()
{
    ui->sobelButton->hide();
    ui->medianButton->hide();
    ui->kernelSize->hide();
    ui->kernelSizeTitle->hide();
    ui->xOrderSlider->hide();
    ui->yOrderSlider->hide();
    ui->zeroXOrderLabel->hide();
    ui->zeroYOrderLabel->hide();
    ui->oneXOrderLabel->hide();
    ui->oneYOrderLabel->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->thresholdTypeSlider->hide();
    ui->CannySlider->hide();
    ui->thresholdTypeLabel->hide();
    ui->thresholdValue->hide();
    ui->dilatationButton->hide();
    ui->dilatationKernelSizeSpinBox->hide();
    ui->dilatationTypeSlider->hide();
    ui->xLabel->hide();
    ui->yLabel->hide();
    ui->dilatationTypeLabel->hide();
    ui->prewittButton->hide();
    ui->billaterialButton->hide();
    ui->label->hide();
    ui->thresholdValueDisplay->hide();
    ui->DoGButton->show();
    ui->sigmasLineEdit->show();
    ui->firstSigmaSpinBox->show();
    ui->secondSigmaSpinBox->show();
    ui->kernelSize->show();
    ui->kernelSizeTitle->show();


}



void IlyaWindow::on_DoGButton_clicked()
{
    Mat firstImage;
    Mat secondImage;
    double firstSigma = ui->firstSigmaSpinBox->value();
    double secondSigma = ui->secondSigmaSpinBox->value();
    if(firstSigma!=0){
        GaussianBlur(src, firstImage, Size(kernelSize,kernelSize), firstSigma);
    }
    else{
        firstImage = src;
    }
    if(secondSigma!=0){
        GaussianBlur(src, secondImage, Size(kernelSize,kernelSize), secondSigma);
    }
    else{
        secondImage = src;
    }
    dst = secondImage - firstImage;
    filteredImage = ASM::cvMatToQImage(dst);
    scene1->clear();
    ui->filteredScene->setScene(scene1);
    filteredImage.convertToFormat(QImage::Format_RGB32);
    scene1->addPixmap(QPixmap::fromImage(filteredImage));

    ui->filteredScene->fitInView(scene1->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();
    popUp->setPopupText("Обработка изображения прошла успешно");
    popUp->show();
    //filteredImage.convertToFormat(QImage::Format_RGB32);

}

void IlyaWindow::on_thresholdValue_valueChanged(int value)
{
    IlyaWindow::on_thresholdValue_sliderMoved(value);
}

void IlyaWindow::on_CannySlider_sliderMoved(int position)
{
    Mat detectedEdges;
    Mat gray;
    int ratio=3;
    int lowThreshold = position;
    int type = src.type();
    if (type!=CV_8U || CV_8UC1)
    {
        cvtColor(src, gray, CV_BGR2GRAY);
    }
    else{
        gray = src;
    }
    dst.create(src.size(),src.type());
    blur(gray, detectedEdges, Size(3,3));
    Canny(detectedEdges,detectedEdges,lowThreshold,lowThreshold*ratio,kernelSize);
    dst = Scalar::all(0);
    src.copyTo(dst, detectedEdges);
    filteredImage = ASM::cvMatToQImage(dst);
    filteredImage.convertToFormat(QImage::Format_RGB32);
    scene1->addPixmap(QPixmap::fromImage(filteredImage));
    ui->filteredScene->fitInView(scene1->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->filteredScene->update();


}

void IlyaWindow::on_CannyRadioButton_clicked()
{
    ui->sobelButton->hide();
    ui->medianButton->hide();
    ui->kernelSize->show();
    ui->kernelSizeTitle->show();
    ui->xOrderSlider->hide();
    ui->yOrderSlider->hide();
    ui->zeroXOrderLabel->hide();
    ui->zeroYOrderLabel->hide();
    ui->oneXOrderLabel->hide();
    ui->oneYOrderLabel->hide();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->thresholdTypeSlider->hide();
    ui->thresholdTypeLabel->hide();
    ui->thresholdValue->hide();
    ui->dilatationButton->hide();
    ui->dilatationKernelSizeSpinBox->hide();
    ui->dilatationTypeSlider->hide();
    ui->xLabel->hide();
    ui->yLabel->hide();
    ui->dilatationTypeLabel->hide();ui->prewittButton->hide();
    ui->billaterialButton->hide();
    ui->label->hide();
    ui->thresholdValueDisplay->hide();
    ui->DoGButton->hide();
    ui->sigmasLineEdit->hide();
    ui->firstSigmaSpinBox->hide();
    ui->secondSigmaSpinBox->hide();
    ui->CannySlider->show();
}

QString* IlyaWindow::getWidgetName()
{
    QString *widgetName = new QString("загружен виджет Ильи");
    return widgetName;
}
