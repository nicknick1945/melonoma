#include "platform_headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "platform_headers/loggerfactory.h"
#include "platform_headers/logger.h"
#include "kolya_headers/utils.h"
#include "QFileDialog"
#include "qpixmap.h"
#include "kolya_headers/startform.h"
#include "platform_headers/defaultwidget.h"
#include "QGraphicsPixmapItem"
#include "kolya_headers/form.h"
#include "qfiledialog.h"
#include "platform_headers/defaultwidgetmodel.h"
#include <functional>
#include "sasha/sashawindow.h"
#include "semion/widget.h"
#include "ilya/ilyawindow.h"
#include "timofey/timofeywindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

    ui->setupUi(this);
    ui->previous->hide();
    widgets = new QList<DefaultWidgetModel*>();
    subProcesses = new QHash<QString,DefaultWidgetModel*>();
    addWidgets();
}

void MainWindow::lockNextNutton()
{
    ui->nextButton->setEnabled(false);
}

void MainWindow::unlockNextButton()
{
    ui->nextButton->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::goToSubProcess(QString subProcessName)
{
    if(subProcesses->contains(subProcessName)){
        widgets->at(currentWidgetNumber)->close();
        QString message = "sub Process name ";
        message.append(subProcessName);
        logger->debug(message);
        currentSubProcessName = new QString(subProcessName);
        subProcesses->value(subProcessName)->show();

    }else {
        logger->error("sub process not found");
    }
}

void MainWindow::returnFromSubProcess()
{
    if(subProcesses->contains(*currentSubProcessName)){
        subProcesses->value(*currentSubProcessName)->close();
        QString message = "return form subprocess name ";
        message.append(*currentSubProcessName);
        logger->debug(message);
        widgets->at(currentWidgetNumber)->onReturnFromSubProcess();
    }else {
        logger->error("mega error nu vse trendec");
    }
}


void MainWindow::setWidgetsGeometry(DefaultWidgetModel &widget){
    widget.widget->setMainWindow(this);
    widget.setGeometry(30,30,900,530);
    widget.close();
}


void MainWindow::next()
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

void MainWindow::on_nextButton_clicked(){
    next();
}

void MainWindow::on_previous_clicked(){
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

    StartForm *startFormWidget = new StartForm(ui->centralWidget);
    DefaultWidgetModel *startForm = new DefaultWidgetModel(startFormWidget);
    setWidgetsGeometry(*startForm);
    startForm->show();
    widgets->append(startForm);

    DefaultWidgetModel *kolaynForm = new DefaultWidgetModel(new Form(ui->centralWidget));
    setWidgetsGeometry(*kolaynForm);
    widgets->append(kolaynForm);

    DefaultWidgetModel *sashaForm = new DefaultWidgetModel(new SashaWidget(ui->centralWidget));
    setWidgetsGeometry(*sashaForm);
    widgets->append(sashaForm);

    DefaultWidgetModel *semionForm= new DefaultWidgetModel(new Widget(ui->centralWidget));
    setWidgetsGeometry(*semionForm);
    widgets->append(semionForm);

    DefaultWidgetModel *timofeyForm = new DefaultWidgetModel(new TimofeyWindow(ui->centralWidget));
    setWidgetsGeometry(*timofeyForm);
    widgets->append(timofeyForm);

    DefaultWidgetModel *ilyaForm= new DefaultWidgetModel(new IlyaWindow(ui->centralWidget));
    setWidgetsGeometry(*ilyaForm);
    widgets->append(ilyaForm);

    SubProcessModel *subProcessModel = new SubProcessModel(startFormWidget);
    subProcesses->insert(*subProcessModel->widget->getWidgetName(),subProcessModel);
    // todo сюды добавлять аналогично как с kolaynForm
}



void MainWindow::on_LoadPhotoButton_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName();
    logger->debug("Путь к загружаемой фотографии:");
    logger->debug(imagePath);
    QImage *originalImage = Utils::loadImage(imagePath);
    cache->setStartImage(originalImage);
}
