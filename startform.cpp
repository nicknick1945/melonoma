#include "startform.h"
#include "ui_startform.h"
#include "cache.h"
#include "cachefactory.h"



StartForm::StartForm(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::StartForm)
{
    ui->setupUi(this);
    Cache* cache = cahceFactory->getInstance();
    QImage* image = new QImage();
    cache->setStartImage(*image);
    QImage image2 = cache->getLoadedImage();

}

QString* StartForm::getWidgetName()
{
    QString *widgetName = new QString("startForm widget");
    return widgetName;
}

StartForm::~StartForm()
{
    delete ui;
}

void StartForm::on_downloadPhotoButton_clicked()
{
}
