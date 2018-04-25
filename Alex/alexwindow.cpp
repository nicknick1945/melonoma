#include "alexwindow.h"
#include "ui_alexwindow.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QVector>
#include <QColor>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

AlexWindow::AlexWindow(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::AlexWindow)
{
    ui->setupUi(this);

    minX=0;
    maxX=0;
    minY=0;
    maxY=0;


    /********************************************************************/
    QMenu *mnfile = new QMenu("Файл"); // Меню файлов (открыть файл и тд)

    QAction *Actionfile = new QAction("Выбрать изображения",mnfile);   //создаю действие в меню "файл"
    connect(Actionfile, SIGNAL(triggered()), this, SLOT(open_image())); //подключаю к действию (action) слот (фукнцию)
    mnfile->addAction(Actionfile);                                     //создаю подпункт в меню "файл"

    QAction *Actionsave = new QAction("Сохранить изображение",mnfile);
    connect(Actionsave, SIGNAL(triggered()), this, SLOT(save_image()));
    mnfile->addAction(Actionsave);

    QAction *Actionquit = new QAction("Выход",mnfile);
    connect(Actionquit, SIGNAL(triggered()), this, SLOT(quit()));
    mnfile->addAction(Actionquit);
    /********************************************************************/
    QMenu * mnfunctions = new QMenu("Функции"); // Меню функции (вызов изображения и тд)

    QAction *Actionopenwindow = new QAction("Открыть изображение в окне",mnfunctions);
    connect(Actionopenwindow, SIGNAL(triggered()), this, SLOT(open_image_window()));
    mnfunctions->addAction(Actionopenwindow);

    QAction *Actionconvert = new QAction("Конвертировать QImage в Mat",mnfunctions);
    connect(Actionconvert, SIGNAL(triggered()), this, SLOT(convert_QImage2Mat()));
    mnfunctions->addAction(Actionconvert);

    QAction *Actionconvert2 = new QAction("Конвертировать Mat в  QImage",mnfunctions);
    connect(Actionconvert2, SIGNAL(triggered()), this, SLOT(convert_Mat2QImage()));
    mnfunctions->addAction(Actionconvert2);
    /********************************************************************/
    QMenu * mnhelp = new QMenu("Справка"); // Меню справки (методика и тд)

    QAction *Actionhelp = new QAction("Тест сообщение в дебаг",mnhelp);
    connect(Actionhelp, SIGNAL(triggered()), this, SLOT(showMessage()));
    mnhelp->addAction(Actionhelp);

    QAction *Actionguide = new QAction("Руководство пользователя",mnhelp);
    connect(Actionguide, SIGNAL(triggered()), this, SLOT(show_guide()));
    mnhelp->addAction(Actionguide);

    ui->menuBar->addMenu(mnfile);
    ui->menuBar->addMenu(mnfunctions);
    ui->menuBar->addMenu(mnhelp);

}

AlexWindow::~AlexWindow()
{
    delete ui;
}

Mat imagemat,imagemat3;
QString path = "mistake"; //строка нужна для передачи пути к изображениям и для проверки на ошибку открытия

void AlexWindow::on_pushButton_contours_clicked()
{
    /*
    Mat img_gray;
    img_gray = imagemat;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(img_gray,contours,hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

    drawContours(imagemat3,contours,-3,CV_RGB(250,0,0),1,8,hierarchy);

    double area = cvContourArea(contours);

    imshow("image",imagemat3);

    imagemat = imagemat3;

    img_gray.release();
    imagemat3.release();
    */

    if(path=="mistake")
        QMessageBox::warning(this,"Внимание!","Изображение не открыто");
    else
    {
        double area; //площадь внутри контура
        double perimeter; //периметр контура
        double form; //коэффициент формы
        double form_value = ui->doubleSpinBox_form_value->value(); //ограничение, вводимое вручную
        int area1; //значение площади в массив
        int form1; //значение формы в массив
        int j=0; //счетчик количества контуров

    IplImage copy = imagemat; //переношу изображение из mat в iplimage
    IplImage* image1 = &copy; //image1 теперь содержит обработанное изображение

    IplImage* img_gray= cvCreateImage( cvSize(image1->width,image1->height), 8, 1); //создаем временное изображение для обработки
    cvCopy(image1,img_gray); //копируем во временное изображение обработанное
    CvSeq* contours=0; //хранилище для контуров
    CvSeq* h_next=0; //
    CvMemStorage* storage = cvCreateMemStorage(0);


    //cvCvtColor( img_gray, img_gray, CV_BGR2GRAY ); //переводим
    //cvThreshold( img_gray, img_gray, 128, 255, CV_THRESH_ );
    if(ui->checkBox_adaptive->isChecked())
    {
        int block = ui->spinBox_adaptive_block->value();
        double param1 = ui->spinBox_adaptive_param1->value();
        cvAdaptiveThreshold(img_gray, img_gray, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C ,CV_THRESH_BINARY, block, param1);
    }

    cvFindContours( img_gray, storage, &contours, sizeof(CvContour),
                    CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cvPoint(0,0) );

    //QListWidgetItem *newItemform1= new QListWidgetItem;
    //QListWidgetItem *newItemarea1 = new QListWidgetItem;

    int conturs_min = 0;
    int conturs_max = 10000;
    double form_max = 10000;

    if(ui->checkBox_conturs->isChecked())
    {
        conturs_min = ui->spinBox_conturs_min->value();
        conturs_max = ui->spinBox_conturs_max->value();
    }

    if(ui->checkBox_form->isChecked())
        form_max = ui->doubleSpinBox_form_value->value();

    for( CvSeq* c=contours; c!=NULL; c=c->h_next ) //считаем, сортируем и записываем площадь и форму
    {
        if (c!=contours)
        {
            area=cvContourArea(c);
            perimeter=cvContourPerimeter(c);
            form = (pow(perimeter,2)/(area));
            if ((c->total<=conturs_min) || (c->total>=conturs_max) || (form>=form_max)) //&&(form>form_value)) //размер удаляемых контуров
            {
                h_next->h_next=h_next->h_next->h_next;
                continue;
            }
        }
        h_next=c;
    }

    QVector<double> bars_form_y(100), bars_form_x(100), bars_area_x(10000), bars_area_y(10000), bars_perimeter_x(1000), bars_perimeter_y(1000);

    for (double i=0;i<form_max;++i) //заполняем массивы нулями
    {
        bars_form_y[i]=0;
        bars_form_x[i]=i;
        ui->listWidget_form_x->addItem(QString::number(bars_form_x[i]));
    }

    for (int i=conturs_min;i<conturs_max;++i) //заполняем массивы нулями
    {
        bars_perimeter_y[i]=0;
        bars_perimeter_x[i]=i;
    }

    for( CvSeq* c=contours; c!=NULL; c=c->h_next ) //считаем кол-во контуров
    {
        //QString strj = QString::number(j);
        //newItemarea1->setText(strj);
        ui->listWidget_j->addItem(QString::number(j));
        j++;
    }

    for (int i=0;i<j;++i) //заполняем массивы нулями
    {
        bars_area_y[i]=0;
        bars_area_x[i]=i;
    }

    for( CvSeq* c=contours; c!=NULL; c=c->h_next )
    {
        area=cvContourArea(c);
        area1 =(area/2)*2;
        ui->listWidget_area->addItem(QString::number(area));
        bars_area_y[area1]++;

        perimeter=cvContourPerimeter(c);
        ui->listWidget_perim->addItem(QString::number(perimeter));
        bars_perimeter_y[perimeter]++;

        form = (pow(perimeter,2)/(area));
        form1=(form/2)*2;
        ui->listWidget_form->addItem(QString::number(form));
        bars_form_y[form1]++;
        ui->listWidget_form_y->addItem(QString::number(bars_form_y[form1]));

    }


/*    for( CvSeq* c=contours; c!=NULL; c=c->h_next )
    {
        CvMoments moments = moments(c,moments);
        double humoments[7];
        CvHuMoments(moment, humoments);
        double humoment;
        for (int i = 0; i<7; i++)
            humoment+=humoments[i];
        humoment = humoment/7;
        ui->listWidget_moments->addItem(QString::number(humoment));

    }

    //if (contours->total<=100)
    //contours=contours->h_next;

*/
    cvDrawContours(image_draw, contours, CV_RGB(255,0,0), CV_RGB(0,255,0),2, 1, CV_AA,
                    cvPoint(0,0));

    cvNamedWindow("image", CV_WINDOW_AUTOSIZE);
    cvShowImage("border", image_draw);
    //cvReleaseImage(image_draw);

    /*............................................................................*/
/*

    int max_form=0; //максимальное значение по вертикали
    for (int i=0;i<100;++i)
    {
        //if(bars_form[i]!=0)
        max_form=(max_form<bars_form[i])?bars_form[i]:max_form;
    }

    int min_form=max_form; //минимальное значение по вертикали
    for (int i=0;i<100;++i)
    {
        if(bars_form[i]!=0)
        min_form=(min_form>bars_form[i])?bars_form[i]:min_form;
    }

    int maxform=0,minform=0; //максимальное значение по горизонтали
    for(int i=0;i<100;++i)
    {
        if(bars_form[i]!=0)
            maxform=i;
    }

    for(int i=100;i<0;--i) //минимальное значение по горизонтали
    {
        if(bars_form[i]!=0)
            minform=i;
    }

    for(int i=0;i<100;++i)
    {
        bars_form_x[i]=i;
    }

    int bars_form_update[k];

    k=0;
    for(int i=0;i<100;++i)
    {
        if(bars_form[i]!=0)
        {
            bars_form[i]=bars_form_update[k];
            k++;
        }

    }

*/

    //строим гистограмму для коэф формы

    int max = (int)getMaxOnVector(bars_form_y,form_max);
    ui->customplot_kf->clearGraphs();
    ui->customplot_kf->addGraph();
    ui->customplot_kf->xAxis->setRange(0,form_max);
    ui->customplot_kf->yAxis->setRange(0, max);
    ui->customplot_kf->xAxis->setLabel("Коэффициент формы");
    ui->customplot_kf->yAxis->setLabel("Кол-во контуров");
    ui->customplot_kf->graph(0)->setData(bars_form_x,bars_form_y);
    ui->customplot_kf->graph(0)->setBrush(QColor(0, 0, 255, 0));
    ui->customplot_kf->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->customplot_kf->replot();

    int min = getMin(bars_form_y, form_max);
    max = getMax(bars_form_y, form_max);
    int mid = getMid(min, max);
    int sko = getSko(min, max, mid);

    ui->min_kf->setText(QString::number(min));
    ui->max_kf->setText(QString::number(max));
    ui->mid_kf->setText(QString::number(mid));
    ui->sko_kf->setText(QString::number(sko));

    //строим гистограмму для площадей

    max = (int)getMaxOnVector(bars_area_y,j);
    ui->customplot_area->clearGraphs();
    ui->customplot_area->addGraph();
    ui->customplot_area->xAxis->setRange(0,j);
    ui->customplot_area->yAxis->setRange(0, max);
    ui->customplot_area->xAxis->setLabel("Площадь");
    ui->customplot_area->yAxis->setLabel("Кол-во контуров");
    ui->customplot_area->graph(0)->setData(bars_area_x,bars_area_y);
    ui->customplot_area->graph(0)->setBrush(QColor(0, 0, 255, 0));
    ui->customplot_area->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->customplot_area->replot();

    min = getMin(bars_area_y, j);
    max = getMax(bars_area_y, j);
    mid = getMid(min, max);
    sko = getSko(min, max, mid);

    ui->min_area->setText(QString::number(min));
    ui->max_area->setText(QString::number(max));
    ui->mid_area->setText(QString::number(mid));
    ui->sko_area->setText(QString::number(sko));

    //строим гистограмму для периметра

    max = (int)getMaxOnVector(bars_perimeter_y,conturs_max);
    ui->customplot_pm->clearGraphs();
    ui->customplot_pm->addGraph();
    ui->customplot_pm->xAxis->setRange(0,conturs_max);
    ui->customplot_pm->yAxis->setRange(0, max);
    ui->customplot_pm->xAxis->setLabel("Площадь");
    ui->customplot_pm->yAxis->setLabel("Кол-во контуров");
    ui->customplot_pm->graph(0)->setData(bars_perimeter_x,bars_perimeter_y);
    ui->customplot_pm->graph(0)->setBrush(QColor(0, 0, 255, 0));
    ui->customplot_pm->setInteractions( QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->customplot_pm->replot();

    min = getMin(bars_perimeter_y, conturs_max);
    max = getMax(bars_perimeter_y, conturs_max);
    mid = getMid(min, max);
    sko = getSko(min, max, mid);

    ui->min_pm->setText(QString::number(min));
    ui->max_pm->setText(QString::number(max));
    ui->mid_pm->setText(QString::number(mid));
    ui->sko_pm->setText(QString::number(sko));




    }
}


/*..................................................................*/
/*.......используемые в основной обработке фильтры (функции)........*/
/*..................................................................*/
void AlexWindow::canny() ///фильтр кэнни с регулировкой параметров
{
    if(path=="mistake")
        QMessageBox::warning(this,"Внимание!","Изображение не открыто");
    else
    {
    Mat imagemat1;
    imagemat1 = imagemat3;
    double min = ui->spinBox_canny_min->value();
    double max = ui->spinBox_canny_max->value();
    int aperture = ui->spinBox_canny_aperture->value();
    bool gradient = false;

    if(ui->checkBox_canny->isChecked())
        gradient = true;
    else gradient = false;

    if(ui->checkBox_canny_blur->isChecked())
        blur(imagemat1, imagemat1, Size(3,3));
    else bool blur = false;

    cvtColor(imagemat1, imagemat1, CV_RGB2GRAY);
    Canny(imagemat1,imagemat1,min,max,aperture,gradient);

    namedWindow("image", CV_WINDOW_FULLSCREEN);
    imshow("image", imagemat1);
    imagemat = imagemat1;
    imagemat1.release();


    }


   /* Mat imagemat1 = imagemat3;
    cvtColor(imagemat1,imagemat1,CV_BGR2GRAY);
    morphologyEx(imagemat1,imagemat1,MORPH_GRADIENT,Mat());
    imshow("border",imagemat1);
    imagemat1.release(); */
}
void AlexWindow::erode_dilate() ///эрозия и дилатация
{
    if(path=="mistake")
        QMessageBox::warning(this,"Внимание!","Изображение не открыто");
    else
    {
    Mat imagemat1 = imagemat; //imagemat1 - временное изображение для работы здесь и в других циклах с imagemat

    if(ui->radioButton_erode->isChecked())
        erode(imagemat1,imagemat1,Mat());
    else if(ui->radioButton_dilate->isChecked())
        dilate(imagemat1,imagemat1,Mat());

    namedWindow("image", CV_WINDOW_FULLSCREEN);
    imshow("image",imagemat1);
    imagemat = imagemat1;
    imagemat1.release();
    }
}
void AlexWindow::smooth() ///медианный фильтр
{
    //if((ui->radioButton_Median->isChecked())&&((median>0)&&(median<10)&&(median%2!=0)))
    if(path=="mistake")
        QMessageBox::warning(this,"Внимание!","Изображение не открыто");
    else
    {
        if(ui->radioButton_Median->isChecked())
        {
            int median_matrix = ui->spinBox_median_matrix->value();
            Mat img_median;
            img_median = imagemat;
            medianBlur(img_median,img_median,median_matrix);
            namedWindow("image", CV_WINDOW_FULLSCREEN);
            imshow("image",img_median);
            imagemat = img_median;
        }
        else if(ui->radioButton_Bilateral->isChecked())
        {
            QMessageBox::warning(this,"Ошибка","Билатеральный фильтр не поддерживается. Пожалуйста, воспользуйтесь медианным фильтром");
            /*int bilateral_matrix = ui->spinBox_bilateral_matrix->value();
            Mat img_bilateral;
            img_bilateral = imagemat;
            bilateralFilter(img_bilateral,img_bilateral,bilateral_matrix,80,80,BORDER_DEFAULT);
            imshow("bilateral_filtered",img_bilateral);
            img_bilateral.release();*/
        }
    }
}


/*..................................................................*/
/*......неиспользуемые в основной обработке фильтры (функции).......*/
/*..................................................................*/
void AlexWindow::sobelqt() ///фильтр собеля в пространстве qimage
{
    if(path=="mistake")
        QMessageBox::warning(this,"Внимание!","Изображение не открыто");
    else
    {
    tmp = img;
    int width = tmp.width()-1, height=tmp.height()-1, X,Y,F;
    QVector <QColor>  pixel;
    QColor it;
    QVector <int> gray;
    QImage result(tmp.width(),tmp.height(),tmp.format());
    int Fmax = ui->spinBox_sobel_threshold->value();
    for(int j=1;j<height;j++)
    {
        for(int i=1;i<width;i++)
        {
            pixel.push_back((QColor)tmp.pixel(i-1,j-1)); //0
            pixel.push_back((QColor)tmp.pixel(i,j-1)); //1
            pixel.push_back((QColor)tmp.pixel(i+1,j-1)); //2
            pixel.push_back((QColor)tmp.pixel(i-1,j)); //3
            pixel.push_back((QColor)tmp.pixel(i,j)); //4
            pixel.push_back((QColor)tmp.pixel(i+1,j)); //5
            pixel.push_back((QColor)tmp.pixel(i-1,j+1)); //6
            pixel.push_back((QColor)tmp.pixel(i,j+1)); //7
            pixel.push_back((QColor)tmp.pixel(i+1,j+1)); //8

            for(int p=0; p<9;p++)
            {
                gray.append(0.3*(pixel.at(p).red()) + 0.59*((pixel.at(p).green())) + 0.11*((pixel.at(p).blue())));
            }

            X=(gray.at(0)+2*gray.at(3)+gray.at(6))-(gray.at(2)+2*gray.at(5)+gray.at(8));
            Y=(gray.at(0)+2*gray.at(1)+gray.at(2))-(gray.at(6)+2*gray.at(7)+gray.at(8));
            F=abs(X)+abs(Y);
            //F=sqrt(pow(X,2)+pow(Y,2));
            if((F>0)&&(F<Fmax))
            {
                it.setRgb(255,255,255);
            }
            else
            {
                it.setRgb(0,0,0);
            }
            result.setPixel(i,j,it.rgb());
            pixel.clear();
            gray.clear();
        }
    }
    S_img->addPixmap(QPixmap::fromImage(result)); //вывожу изображение
    img = result; //передаю результат дальше в функцию конвептации
    }
}
void AlexWindow::laplace() ///лаплас в mat
{
    if(path=="mistake")
        QMessageBox::warning(this,"Внимание!","Изображение не открыто");
    else
    {
    Mat imagemat1 = imagemat;
    int laplace_matrix = ui->spinBox_matrix->value();

    Mat grayImg, laplacianImg, laplacianImgAbs;

    GaussianBlur(imagemat1, imagemat1, Size(3,3), 0, 0, BORDER_DEFAULT);
    cvtColor(imagemat1, grayImg, CV_RGB2GRAY);
    Laplacian(grayImg,laplacianImg,CV_16S,laplace_matrix,1,0,BORDER_DEFAULT);
    convertScaleAbs(laplacianImg,laplacianImgAbs);

    imagemat = laplacianImgAbs;
    convert_Mat2QImage();

        imagemat1.release();
        grayImg.release();
        laplacianImg.release();
        laplacianImgAbs.release();
    }
}
void AlexWindow::sobel() ///собель в mat
{
    if(path=="mistake")
        QMessageBox::warning(this,"Внимание!","Изображение не открыто");
    else
    {
    Mat imagemat1 = imagemat;
    int x = ui->spinBox_sobel_x->value();
    int y = ui->spinBox_sobel_y->value();
    int matrix = ui->spinBox_matrix->value();

    Mat grayImg, sobelImg, sobelImgAbs;

    if(ui->checkBox_blur->isChecked())
        GaussianBlur(imagemat1, imagemat1, Size(3,3), 0, 0, BORDER_DEFAULT);
    cvtColor(imagemat1, grayImg, CV_RGB2GRAY);
    Sobel(grayImg,sobelImg,CV_16S,x,y,matrix);
    convertScaleAbs(sobelImg,sobelImgAbs);

        imagemat = sobelImgAbs;

        imagemat1.release();
        grayImg.release();
        sobelImg.release();
        sobelImgAbs.release();

    /*
    IplImage* img_sobel1 =  cvCreateImage( cvSize(image->width, image->height), IPL_DEPTH_16S, image->nChannels);
    IplImage* img_sobel2 = cvCreateImage( cvGetSize(image),IPL_DEPTH_8U, image->nChannels);

    cvSobel(image, img_sobel1, x, y, matrix);
    cvLaplace(image, img_sobel1,3);
    cvConvertScale(img_sobel1,img_sobel2);
    cvShowImage("sobel", img_sobel1);
    cvReleaseImage(&img_sobel1);
    cvReleaseImage(&img_sobel2);
    */
    /*
    IplImage* img_morfology=cvCreateImage(cvSize(image->width,image->height), 8, 3);
    IplImage* temp= cvCreateImage(cvSize(image->width,image->height), 8, 3);
    IplConvKernel* structuringElement;
    int rows=2;
    int columns=2;
    structuringElement = cvCreateStructuringElementEx(rows, columns, cvFloor(rows / 2),
                                                      cvFloor(columns / 2), CV_SHAPE_RECT, NULL);
    cvMorphologyEx(image,img_morfology,temp,structuringElement,CV_MOP_GRADIENT,1);
    cvShowImage( "morfology", img_morfology);
    */

    }
}
void AlexWindow::filter_matrix() ///фильтр наложение матрицы
{
    if(path=="mistake")
        QMessageBox::warning(this,"Внимание!","Изображение не открыто");
    else
    {
    // константы для хранения ядра фильтра
       const int kernelData[9] = {-1,-1,-1,
                                 -1,9,-1,
                                 -1,-1,-1};

      /* {8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8,
       8, 4, 2, 1, -1, -2, -24, -2, -1, 1, 2, 4, 8}; */

       const Mat kernel(3, 3, CV_8UC1, (int *)kernelData);

       Mat imagemat1 = imagemat;

       //cvtColor(imagemat1, imagemat1, CV_RGB2GRAY);

       filter2D(imagemat1, imagemat1, -1, kernel);
       convertScaleAbs(imagemat1,imagemat1);

       namedWindow("image", CV_WINDOW_FULLSCREEN);
       imshow("image",imagemat1);
       imagemat = imagemat1;
       imagemat1.release();
    }
}


/*..................................................................*/
/*.....................кнопки для вызова функций....................*/
/*..................................................................*/
void AlexWindow::on_pushButton_smooth_clicked() ///кнопка медианный фильтр
{
    smooth();
}
void AlexWindow::on_pushButton_canny_clicked() ///кнопка фильтр кэнни
{
    canny();
}
void AlexWindow::on_pushButton_erode_dilate_clicked() ///кнопка эрозия и дилатация
{
    erode_dilate();
}
void AlexWindow::on_pushButton_filter_matrix_clicked() ///кнопка фильтр наложение матрицы
{
    filter_matrix();
}
void AlexWindow::on_pushButton_magic_clicked() ///все операции обработки сразу по очереди
{
    if(path=="mistake")
        QMessageBox::warning(this,"Внимание!","Изображение не открыто");
    else
    {
        {
            Mat imagemat1;
            imagemat1 = imagemat3;
            double min = ui->spinBox_canny_min->value();
            double max = ui->spinBox_canny_max->value();
            int aperture = ui->spinBox_canny_aperture->value();
            bool gradient = false;

            if(ui->checkBox_canny->isChecked())
                gradient = true;
            else gradient = false;

            if(ui->checkBox_canny_blur->isChecked())
                blur(imagemat1, imagemat1, Size(3,3));
            else bool blur = false;

            cvtColor(imagemat1, imagemat1, CV_RGB2GRAY);
            Canny(imagemat1,imagemat1,min,max,aperture,gradient);

            namedWindow("image", CV_WINDOW_FULLSCREEN);
            imshow("image", imagemat1);
            imagemat = imagemat1;
            imagemat1.release();
        }

        {
            Mat imagemat1 = imagemat;
            dilate(imagemat1,imagemat1,Mat());
            //namedWindow("image", CV_WINDOW_FULLSCREEN);
            //imshow("image",imagemat1);
            imagemat = imagemat1;
            imagemat1.release();
        }

        {
            Mat img_median;
            img_median = imagemat;
            medianBlur(img_median,img_median,5);
            //namedWindow("image", CV_WINDOW_FULLSCREEN);
            //imshow("image",img_median);
            imagemat = img_median;
            img_median.release();
        }

        {
            Mat img_median;
            img_median = imagemat;
            medianBlur(img_median,img_median,5);
            //namedWindow("image", CV_WINDOW_FULLSCREEN);
            //imshow("image",img_median);
            imagemat = img_median;
            img_median.release();
        }

        {
            Mat img_median;
            img_median = imagemat;
            medianBlur(img_median,img_median,5);
            //namedWindow("image", CV_WINDOW_FULLSCREEN);
            //imshow("image",img_median);
            imagemat = img_median;
            img_median.release();
        }

        {
            Mat imagemat1 = imagemat;
            dilate(imagemat1,imagemat1,Mat());
            //namedWindow("image", CV_WINDOW_FULLSCREEN);
            //imshow("image",imagemat1);
            imagemat = imagemat1;
            imagemat1.release();
        }

        {
            Mat img_median;
            img_median = imagemat;
            medianBlur(img_median,img_median,5);
            //namedWindow("image", CV_WINDOW_FULLSCREEN);
            //imshow("image",img_median);
            imagemat = img_median;
            img_median.release();
        }

        {
            Mat img_median;
            img_median = imagemat;
            medianBlur(img_median,img_median,5);
            //namedWindow("image", CV_WINDOW_FULLSCREEN);
            //imshow("image",img_median);
            imagemat = img_median;
            img_median.release();
        }

        {
            Mat img_median;
            img_median = imagemat;
            medianBlur(img_median,img_median,5);
            //namedWindow("image", CV_WINDOW_FULLSCREEN);
            //imshow("image",img_median);
            imagemat = img_median;
            img_median.release();
        }

        {
            Mat imagemat1 = imagemat;
            erode(imagemat1,imagemat1,Mat());
            namedWindow("image", CV_WINDOW_FULLSCREEN);
            imshow("image",imagemat1);
            imagemat = imagemat1;
            imagemat1.release();
        }

        {
            Mat imagemat1 = imagemat;
            erode(imagemat1,imagemat1,Mat());
            namedWindow("image", CV_WINDOW_FULLSCREEN);
            imshow("image",imagemat1);
            imagemat = imagemat1;
            imagemat1.release();
        }
    }
}


/*..................................................................*/
/*.............неиспользуемые кнопки для вызова функций.............*/
/*..................................................................*/
void AlexWindow::on_pushButton_sobelqt_clicked() ///кнопка фильтр собеля в пространстве qimage
{
    sobelqt();
    convert_QImage2Mat();
}
void AlexWindow::on_pushButton_sobel_clicked() ///кнопка собель в mat
{
    sobel();
}
void AlexWindow::on_pushButton_laplace_clicked() ///кнопка лаплас в mat
{
    laplace();
}


/*..................................................................*/
/*.....................функции для разделов меню....................*/
/*..................................................................*/
void AlexWindow::open_image() /// записать пути выбранных картинок в str и вывести в listwidget
{
    int itcnt=0;
    QStringList str = QFileDialog::getOpenFileNames();
    for(QStringList::iterator it=str.begin();it!=str.end();++it)
    {
        ui->path->addItem(*it);
        itcnt++;
    }
}
void AlexWindow::save_image() ///сохранить последний резальтат обработки
{
    if(path=="mistake")
        QMessageBox::warning(this,"Внимание!","Изображение не открыто");
    else
    {
    QString filename = QFileDialog::getSaveFileName(0, "Сохранить как...",QDir::currentPath(),"All types(*.*);;PNG (*.png);;JPG (*.jpeg *.jpg);; BMP (*.bmp)");
    String str = filename.toStdString();
    imwrite(str.c_str(),imagemat);
    }

}
void AlexWindow::quit() ///выйти из приложения
{
    qApp->quit();
}
void AlexWindow::open_image_window() ///открыть последний результат обработки в отдельном окне
{

    Mat image;
    image = imagemat;
    imshow("Изображение",image);


    cvtColor(image,image,COLOR_BGR2HLS);

    vector<Mat> channels;
    split(image, channels);

    namedWindow("H channel (gray)", WINDOW_AUTOSIZE);
    imshow("H channel (gray)", channels[0]);
    namedWindow("L channel (gray)", WINDOW_AUTOSIZE);
    imshow("L channel (gray)", channels[1]);
    namedWindow("S channel (gray)", WINDOW_AUTOSIZE);
    imshow("S channel (gray)", channels[2]);

    namedWindow("HLS image (all chanels)", WINDOW_AUTOSIZE);
    imshow("HLS image (all chanels)", image);

    image.release();
}
void AlexWindow::show_guide() ///показать методику
{
   QMessageBox::warning(this,"Внимание!","База данных отключена");
}
void AlexWindow::showMessage() ///проверка работы меню
{
qDebug() << "menu clicked";
}


/*..................................................................*/
/*........................функции конвертеров.......................*/
/*..................................................................*/
void AlexWindow::convert_QImage2Mat() ///конвертер
{
    img = img.convertToFormat(QImage::Format_Grayscale8);
    cv::Mat  mat(img.height(),img.width(),CV_8UC1,const_cast<uchar*>(img.bits()),
                 static_cast<size_t>(img.bytesPerLine())
                 );
    imagemat = mat;
}
void AlexWindow::convert_Mat2QImage() //конвертер
{

}


/*..................................................................*/
/*..............................методы..............................*/
/*..................................................................*/
void AlexWindow::on_path_itemClicked(QListWidgetItem *item) ///вывести картинку по щелчку на listwidget
{
    path = item->text();
    String str = path.toStdString();

    image_draw = cvLoadImage(str.c_str(),1);
    image = cvLoadImage(str.c_str(),1); //картинку в память для манипуляций в пространстве iplimage
    imagemat  = imread(str.c_str(),1); //картинку в память для манипуляций в пространстве mat
    imagemat3 = imread(str.c_str(),1); //картинку в память как эталон в пространстве mat
    img.load(item->text());

    S_img  = new QGraphicsScene;
    ui->graphicsView->setScene(S_img);
    S_img->addPixmap(QPixmap::fromImage(img)); //вывод картинки
}
void AlexWindow::on_horizontalSlider_valueChanged() ///функция масштабирования картинки в graphicsView
{
    value1 = ui->horizontalSlider->value();

    if((value1-value2)<0)
    {
        ui->graphicsView->scale(1/1.1,1/1.1);
        value2 = value1;
    }
    if((value1-value2)>0)
    {
        ui->graphicsView->scale(1.1,1.1);
        value2 = value1;
    }
}


/*..................................................................*/
/*......................функции для гистограмм......................*/
/*..................................................................*/
double AlexWindow::getMaxOnVector(QVector<double> vec,int size) ///поиск максимума на векторе
{
    maXX = 0;
    double result = vec[0];
    for(int i=0; i<size;i++)
    {
        if(vec[i]>result)
        {
            result = vec[i];
            maXX = i;
        }
    }
    return result;
}
double AlexWindow::getMidOnVector(QVector<double> vec,int size) ///поиск середины вектора
{
    double result = 0;
    for(int i=0; i<size;i++)
    {
        result += vec[i];
    }
    return result/(double)size;
}
double AlexWindow::getSKOOnVector(QVector<double> vec,int size, double mid) ///поиск ско вектора
{
    double result = 0;
    for(int i=0; i<size;i++)
    {
        result += (vec[i]-mid)*(vec[i]-mid);
    }
    return sqrt(result/(double)size);
}
int AlexWindow::getMin(QVector<double> vec,int size) ///минимум по абсциссе
{
    int result = 0;
    for(int i=0; i<size; i++)
    {
        if(vec[i]>0)
        {
            result = i;
            break;
        }
    }
    return result;
}
int AlexWindow::getMax(QVector<double> vec,int size) ///максимум по абсциссе
{
    int result = size-1;
    for(int i=size-1; i>0; i--)
    {
        if(vec[i]>0)
        {
            result = i;
            break;
        }
    }
    return result;
}
int AlexWindow::getMid(int min, int max) ///середина(МО) по абсциссе
{
    int result = 0;
    for(int i=min; i<max; i++)
    {
        result +=i;
    }
    return result/(max - min);
}
int AlexWindow::getSko(int min, int max, int mid) ///ско по абсциссе
{
    int result = 0;
    for(int i=min; i<max; i++)
    {
        result += (i - mid) * (i - mid);
    }
    return sqrt(result/(max - min));
}


/*..................................................................*/
/*.........................временные файлы..........................*/
/*..................................................................*/
void AlexWindow::temp()
{
    /*.....................старая гистограмма..........................
     *
     *
        //CvHistogram* cvCreateHist(k,bars_area_update,CV_HIST_ARRAY);
        int hist_size = k;

          //CvHistogram *hist;
          IplImage *hist_image = cvCreateImage(cvSize(100,20), 8, 1);

          //hist = cvCreateHist(k,bars_form_update,CV_HIST_ARRAY);
          //cvCalcHist( &gray, hist, 0, NULL );

          int x=0,y=0,h=0,w=2;
          for(int i=0; i<hist_size; i++ )
          {
              h=bars_form_update[i];
              y=0;
              x+=2;
              w+=2;
              cvRectangle(hist_image, cvPoint(x,y),cvPoint(w,h),cvScalarAll(0), 1, 8, 0);
          }
          cvNamedWindow( "histogram",1);
          cvShowImage( "histogram", hist_image );

          */

    /*.................работа с путями изображений......
     *
     *
    //path_to-img = item->text();
    //str.insert(0,"\"");
    //str.insert(str.length(),"\"");
    //ui->lineEdit->insert(str);
    //ui->lineEdit->setText(str);
    //QByteArray qb = str.toLocal8Bit();
    //char* filename = qb.data();
    //ui->label->setText(filename); */

    /*.................конвертер iplimage to qimage...........................
     *
     *
    QImage img(image->width,image->height,QImage::Format_RGB888);
    for (int x=0;x<img.width();++x)
        for(int y=0;y<img.height();++y)
        {
            CvScalar s = cvGet2D(imagemat,y,x);
            int R = double(s.val[2]);
            int G = double(s.val[1]);
            int B = double(s.val[0]);
            img.setPixel(x,y,qRgb(R,G,B));
        }
    */

    /*.................неработающий конвертер mat to qimage....................
     *
     *
        QImage imgimg ((const uchar *) imagemat.data, imagemat.cols, imagemat.rows, imagemat.step, QImage::Format_Grayscale8);
        //imgimg.bits(); // enforce deep copy, see documentation

        //img = imgimg;
        S_img  = new QGraphicsScene;
        ui->graphicsView->setScene(S_img);
        S_img->clear();
        S_img->addPixmap(QPixmap::fromImage(imgimg));

    // QImage imgimg(imagemat.data,imagemat.cols, imagemat.rows,
    //                      static_cast<int>(imagemat.step),QImage::Format_Grayscale8);
    */
}

QString* AlexWindow::getWidgetName()
{
    QString *widgetName = new QString("Лешин виджет widget");
    return widgetName;
}

