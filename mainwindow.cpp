#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loggerfactory.h"
#include "logger.h"
#include "utils.h"
#include "QFileDialog"
#include "qpixmap.h"
#include "startform.h"
#include "defaultwidget.h"
#include "QGraphicsPixmapItem"
#include "form.h"
#include "qfiledialog.h"
#include "defaultwidgetmodel.h"
#include <functional>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->previous->hide();
    widgets = new QList<DefaultWidgetModel*>();
    addWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setWidgetsGeometry(DefaultWidgetModel &widget)
{
    widget.setGeometry(30,30,900,530);
    widget.close();
}


void MainWindow::on_nextButton_clicked()
{

    for(int i = 0 ; i < widgets->size() ; i ++ ){
        widgets->at(i)->close();
    }
    ui->previous->show();
    widgets->at(currentWidgetNumber+1)->show();
    if(currentWidgetNumber+1 == widgets->size()-1){
        ui->nextButton->hide();
    }
    currentWidgetNumber = currentWidgetNumber+1;
    this->update();


}

void MainWindow::on_previous_clicked()
{
    for(int i = 0 ; i < widgets->size() ; i ++ ){
        widgets->at(i)->close();
    }
    ui->nextButton->show();
    widgets->at(currentWidgetNumber-1)->show();
    if(currentWidgetNumber-1 == 0){
        ui->previous->close();
    }
    currentWidgetNumber = currentWidgetNumber-1;
    this->update();
}

void MainWindow::addWidgets()
{

    DefaultWidgetModel *startForm = new DefaultWidgetModel(new StartForm(ui->centralWidget));
    setWidgetsGeometry(*startForm);
    startForm->show();
    widgets->append(startForm);

    DefaultWidgetModel *kolaynForm = new DefaultWidgetModel(new Form(ui->centralWidget));
    setWidgetsGeometry(*kolaynForm);
    widgets->append(kolaynForm);

    // todo сюды добавлять аналогично как с kolaynForm
}


void MainWindow::on_LoadPhotoButton_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName();
    logger->debug("Путь к загружаемой фотографии:");
    logger->debug(imagePath);
    QImage *originalImage = Utils::loadImage(imagePath);
}
