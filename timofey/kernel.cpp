#include "kernel.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

Kernel::Kernel()
{
    timofeyWindow = new TimofeyWindow();
    scene = new QGraphicsScene();
    scene2 = new QGraphicsScene();
    timofeyWindow->show();
    timofeyWindow->loadSceneIntoGraphicsView(scene);
    timofeyWindow->loadSceneIntoGraphicsView_2(scene2);

    connect(timofeyWindow, SIGNAL(loadImageButton_clicked()), this, SLOT(loadImage()));
    connect(timofeyWindow, SIGNAL(KmeansButton_clicked(QString)), this, SLOT(KmeansMethod(QString)));
    connect(timofeyWindow, SIGNAL(saveButton_clicked()), this, SLOT(saveImage()));
}

Kernel::~Kernel()
{

}

void Kernel::loadImage()
{
    imagePath = QFileDialog::getOpenFileName(timofeyWindow, "Select image to open...", QDir::currentPath(), "Images (*.png *.gif *.jpg *.bmp);;All Files(*.*)");
    if (imagePath != "")
    {
        defaultImage.load(imagePath);
        defaultImage.convertToFormat(QImage::Format_RGB888);
        binaryImage = defaultImage;
        timofeyWindow->eraseParams();
        scene->clear();
        scene2->clear();
        scene->addPixmap(QPixmap::fromImage(defaultImage));
    }
}

void Kernel::saveImage()
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

void Kernel::KmeansMethod(QString textEntry)
{
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

    timofeyWindow->paramsToLabels(calculateFeatures(binaryImage));
}

QPixmap Kernel::makeTransparentImage(QImage &image, int transparency)
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

QVector<double> Kernel::calculateFeatures(QImage &image)
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
