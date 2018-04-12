#include "timofeywindow.h"
#include "ui_timofeywindow.h"
#include "timofey/timofeyzoom.h"
#include "qfiledialog.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "qmessagebox.h"
#include "haralickfeatures.h"

using namespace cv;
using namespace std;


TimofeyWindow::TimofeyWindow(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::TimofeyWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    scene2 = new QGraphicsScene();
    loadSceneIntoGraphicsView(scene);
    loadSceneIntoGraphicsView_2(scene2);
}

TimofeyWindow::~TimofeyWindow()
{
    delete ui;
}

void TimofeyWindow::on_pushButton_clicked()
{
   imagePath = QFileDialog::getOpenFileName();
    if (imagePath != "")
    {
        defaultImage.load(imagePath);
        defaultImage.convertToFormat(QImage::Format_RGB888);
        binaryImage = defaultImage;
        eraseParams();
        scene->clear();
        scene2->clear();
        scene->addPixmap(QPixmap::fromImage(defaultImage));
    }
}

void TimofeyWindow::on_pushButton_2_clicked()
{
    QString  textEntry =  ui->lineEdit->text();
    Mat src = imread(imagePath.toStdString(), 1);
    Mat samples(src.rows * src.cols, 3, CV_32F);
    for( int y = 0; y < src.rows; y++ )
      for( int x = 0; x < src.cols; x++ )
        for( int z = 0; z < 3; z++)
          samples.at<float>(y + x*src.rows, z) = src.at<Vec3b>(y,x)[z];

    int clusterCount = textEntry.toInt();
    if (clusterCount == 0 || clusterCount > 50)
        return;

    Mat labels;
    int attempts = 5;
    Mat centers;

    kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);

    Mat new_image( src.size(), src.type() );
    for( int y = 0; y < src.rows; y++ )
      for( int x = 0; x < src.cols; x++ )
      {
        int cluster_idx = labels.at<int>(y + x*src.rows,0);
        new_image.at<Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
        new_image.at<Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
        new_image.at<Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
      }

    clusteredImage = QImage((uchar*) new_image.data, new_image.cols, new_image.rows, new_image.step, QImage::Format_RGB888);

    vector<int> colors;
    colors.push_back(clusteredImage.pixelColor(defaultImage.width() / 2, defaultImage.height() / 2).red());
    colors.push_back(clusteredImage.pixelColor(defaultImage.width() / 2, defaultImage.height() / 2).green());
    colors.push_back(clusteredImage.pixelColor(defaultImage.width() / 2, defaultImage.height() / 2).blue());

    for (int i = 0; i < defaultImage.width(); ++i)
        for (int j = 0; j < defaultImage.height(); ++j)
            if (clusteredImage.pixelColor(i, j).red() != colors[0] && clusteredImage.pixelColor(i, j).green() != colors[1] && clusteredImage.pixelColor(i, j).blue() != colors[2])
                binaryImage.setPixelColor(i, j, QColor(255, 255, 255, 255));

    scene2->addPixmap(QPixmap::fromImage(defaultImage));
    scene2->addPixmap(makeTransparentImage(clusteredImage, 130));

    paramsToLabels(calculateFeatures(binaryImage));
//    emit KmeansButton_clicked(ui->lineEdit->text());
}

void TimofeyWindow::loadSceneIntoGraphicsView(QGraphicsScene *scene)
{
    ui->graphicsView->setScene(scene);
}

void TimofeyWindow::loadSceneIntoGraphicsView_2(QGraphicsScene *scene)
{
    ui->graphicsView_2->setScene(scene);
}

void TimofeyWindow::on_pushButton_3_clicked()
{

    if (binaryImage.width() != 0)
    {
        QString savePath = QFileDialog::getSaveFileName();
        if (savePath != "")
            binaryImage.save(savePath + ".png");
    }
    else
    {
        QMessageBox msg;
        msg.setText("Nothing to save!");
        msg.exec();
    }
}

void TimofeyWindow::paramsToLabels(QVector<double> params)
{
    ui->label->setText("ВТОРОЙ УГЛОВОЙ МОМЕНТ: " + QString::number(params[0]));
    ui->label_2->setText("КОНТРАСТНОСТЬ: " + QString::number(params[1]));
    ui->label_3->setText("КОРЕЛЛЯЦИЯ: " + QString::number(params[2]));
    ui->label_4->setText("СУММА КВАДРАТОВ: " + QString::number(params[3]));
    ui->label_5->setText("ГОМОГЕННОСТЬ: " + QString::number(params[4]));
    ui->label_6->setText("СРЕДНЕЕ ПО СУММАМ: " + QString::number(params[5]));
    ui->label_7->setText("ДИСПЕРСИЯ СУММ: " + QString::number(params[6]));
    ui->label_8->setText("ЭНТРОПИЯ СУММ: " + QString::number(params[7]));
    ui->label_9->setText("ЭНТРОПИЯ: " + QString::number(params[8]));
    ui->label_10->setText("ДИСПЕРСИЯ РАЗНОСТЕЙ: " + QString::number(params[9]));
    ui->label_11->setText("ЭНТРОПИЯ РАЗНОСТЕЙ: " + QString::number(params[10]));
}

void TimofeyWindow::eraseParams()
{
    ui->label->setText("");
    ui->label_2->setText("");
    ui->label_3->setText("");
    ui->label_4->setText("");
    ui->label_5->setText("");
    ui->label_6->setText("");
    ui->label_7->setText("");
    ui->label_8->setText("");
    ui->label_9->setText("");
    ui->label_10->setText("");
    ui->label_11->setText("");
    ui->label_12->setText("");
}

QPixmap TimofeyWindow::makeTransparentImage(QImage &image, int transparency)
{
    if (transparency < 0 || transparency > 255)
        transparency = 0;

    QPixmap transparent(image.size());
    transparent.fill(Qt::transparent);
    QPainter p;
    p.begin(&transparent);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawPixmap(0, 0, QPixmap::fromImage(image));
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.fillRect(transparent.rect(), QColor(0, 0, 0, transparency));
    p.end();

    return transparent;
}

QVector<double> TimofeyWindow::calculateFeatures(QImage &image)
{
    HaralickFeatures features(image, 1);
    QVector<double> params;
    params.push_back(features.asn);
    params.push_back(features.con);
    params.push_back(features.cor);
    params.push_back(features.sos);
    params.push_back(features.idm);
    params.push_back(features.sav);
    params.push_back(features.sva);
    params.push_back(features.sen);
    params.push_back(features.ent);
    params.push_back(features.dva);
    params.push_back(features.den);
    params.push_back(0);

    return params;
}

QString* TimofeyWindow::getWidgetName()
{
    QString *widgetName = new QString("загружен виджет тимофея");
    return widgetName;
}
