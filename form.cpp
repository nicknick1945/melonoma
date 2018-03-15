#include "form.h"
#include "ui_form.h"
#include "loggerfactory.h"
#include "logger.h"
#include "utils.h"
#include "QFileDialog"
#include "qpixmap.h"
#include "QGraphicsPixmapItem"

Form::Form(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}


void Form::on_downloadPhotoButton_clicked(){
    QString imagePath = QFileDialog::getOpenFileName();
    logger->debug("Путь к загружаемой фотографии:");
    logger->debug(imagePath);
    originalImage = Utils::loadImage(imagePath);
    superOriginalImage = Utils::loadImage(imagePath);
    setImageToScenOriginal(*superOriginalImage);
    engine->doFilter(*originalImage);
    setImageToScen(*originalImage);
}

void Form::setImageToSceneMin(QImage &image){
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    QGraphicsPixmapItem* pixmap_item = new QGraphicsPixmapItem();
    scene->addItem(pixmap_item);
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap_item->setVisible(true);
    pixmap_item->setPixmap(pixmap);
    scene->setSceneRect(0, 0, pixmap.width(), pixmap.height());
    ui->graphicsView->fitInView(pixmap_item, Qt::KeepAspectRatio);
}

void Form::setImageToScen(QImage &image)
{
    bool isRealSize = ui->sizeCheckBox->checkState()==Qt::CheckState::Checked;
    if(isRealSize){
        setMaxSizeImageToScene(image);
    }else{
        setImageToSceneMin(image);
    }
}


void Form::setMaxSizeImageToScene(QImage &image){
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->update();
}

void Form::setImageToSceneMinOriginal(QImage &image)
{
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView_2->setScene(scene);
    QGraphicsPixmapItem* pixmap_item = new QGraphicsPixmapItem();
    scene->addItem(pixmap_item);
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap_item->setVisible(true);
    pixmap_item->setPixmap(pixmap);
    scene->setSceneRect(0, 0, pixmap.width(), pixmap.height());
    ui->graphicsView_2->fitInView(pixmap_item, Qt::KeepAspectRatio);
}

void Form::setImageToScenOriginal(QImage &image)
{
    bool isRealSize = ui->sizeCheckBox->checkState()==Qt::CheckState::Checked;
    if(isRealSize){
        setMaxSizeImageToSceneOriginal(image);
    }else{
        setImageToSceneMinOriginal(image);
    }
}

void Form::setMaxSizeImageToSceneOriginal(QImage &image)
{
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(image));
    ui->graphicsView_2->setScene(scene);
    ui->graphicsView_2->update();
}



void Form::on_toBinaryButton_clicked()
{
    bool isInverse = ui->inverseCheckBox->checkState()==Qt::CheckState::Checked;

    QImage image = engine->doBinary(*originalImage,ui->spinBox->value(),isInverse);
    *tempImage = image;
    double persentVolos = engine->culculatePersentVolos(*tempImage);
    ui->persontVolos->setText(QString::number(persentVolos));
    setImageToScen(image);
}

void Form::on_revertButton_clicked()
{
    setImageToScen(*originalImage);
}

void Form::on_spinBox_valueChanged(int arg1)
{
    bool isInverse = ui->inverseCheckBox->checkState()==Qt::CheckState::Checked;
    QImage image = engine->doBinary(*originalImage,arg1,isInverse);
    logger->debug(QString::number(image.height()));
    *tempImage = image;
    logger->debug(QString::number(tempImage->height()));
    double persentVolos = engine->culculatePersentVolos(*tempImage);
    ui->persontVolos->setText(QString::number(persentVolos));
    setImageToScen(*tempImage);
}

void Form::on_pushButton_clicked()
{
    engine->doFilterPomeh(*tempImage);
    setImageToScen(*tempImage);
}

void Form::on_pushButton_2_clicked()
{
    engine->doSkiletization(*tempImage);
    setImageToScen(*tempImage);
}

void Form::on_culculateCountVolos_clicked()
{
    int countVolos = engine->culculateCountVolos(*tempImage);
    ui->countvolosLabel->setText(QString::number(countVolos));
}

QString* Form::getWidgetName()
{
    QString *widgetName = new QString("распознаватель волос widget");
    return widgetName;
}
