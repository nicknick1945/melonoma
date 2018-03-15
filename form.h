#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "loggerfactory.h"
#include "logger.h"
#include "engine.h"
#include "defaultwidget.h"

namespace Ui {
class Form;
}

class Form : public DefaultWidget
{
    Q_OBJECT

public:
    LoggerFactory *loggerFactory = new LoggerFactory();
    Logger *logger = loggerFactory->getInstance();
    QImage *originalImage;
    QImage *superOriginalImage;
    QImage *tempImage = new QImage();
    Engine *engine = new Engine();
    QString* getWidgetName();
    explicit Form(QWidget *parent = 0);
    ~Form();

private slots:
    void on_downloadPhotoButton_clicked();

    void on_toBinaryButton_clicked();

    void on_revertButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_culculateCountVolos_clicked();


private:
    Ui::Form *ui;
    bool realSize = true;
    void setImageToSceneMin(QImage &image);
    void setImageToScen(QImage &image);
    void setMaxSizeImageToScene(QImage &image);
    void setImageToSceneMinOriginal(QImage &image);
    void setImageToScenOriginal(QImage &image);
    void setMaxSizeImageToSceneOriginal(QImage &image);
};

#endif // FORM_H
