#include "kolya_headers/startform.h"
#include "ui_startform.h"
#include "platform_headers/cache.h"
#include "platform_headers/cachefactory.h"



StartForm::StartForm(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::StartForm)
{
    ui->setupUi(this);
    Cache* cache = cahceFactory->getInstance();
    QImage* image = new QImage();
    cache->setStartImage(image);
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

void StartForm::on_pushButton_clicked()
{
    nextWidget();
}

void StartForm::on_pushButton_2_clicked()
{
    lockNextButton();
}

void StartForm::on_testSubProcess_clicked()
{
    returnFromSubProcess();
}
