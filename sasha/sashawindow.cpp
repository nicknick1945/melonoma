#include "sashawindow.h"
#include "ui_sashawindow.h"


SashaWidget::SashaWidget(QWidget *parent) :
    DefaultWidget(parent),
    ui(new Ui::SashaWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene_2 = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView_2->setScene(scene_2);
    load_flag = false;
    proc_flag = false;

    this->setWindowState(Qt::WindowMaximized);
}

SashaWidget::~SashaWidget()
{
    delete ui;
}

void SashaWidget::on_pushButton_clicked()
{
    scene->clear();
    scene_2->clear();
    load_flag = false;
    proc_flag = false;
    fileName = QFileDialog::getOpenFileName();
    if (!fileName.isEmpty())
    {
        QImage image(fileName);
        if (image.isNull())
            QMessageBox::information(this, tr("Предупреждение"),tr("Невозможно загрузить %1.").arg(fileName));
        else
        {
            img.load(fileName);
            img=img.convertToFormat(QImage::Format_RGB888);
            scene->addPixmap(QPixmap::fromImage(img));
            load_flag = true;
        }
    }
}

void SashaWidget::on_pushButton_2_clicked()
{
    if (load_flag && !proc_flag)
    {
        dst = img;
        dst_2 = img;
        ImageMatrix m1 (img);
        Processing pr;
        pr.bilateral(m1, 2, 10, 15);
        auto begin = std::chrono::steady_clock::now();
        pr.my_filter(m1);
        auto end = std::chrono::steady_clock::now();
        qDebug() << "Filtering:" << (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)).count() << "ms";
        auto begin_2 = std::chrono::steady_clock::now();
        pr.counting(m1,300,img);
        auto end_2 = std::chrono::steady_clock::now();
        qDebug() << "Deleting small:" << (std::chrono::duration_cast<std::chrono::milliseconds>(end_2 - begin_2)).count() << "ms";
        m1.to_image(dst);
        dst.save(fileName.split(".").at(0) + "_mask.jpg", "PNG");
        scene_2->addPixmap(QPixmap::fromImage(dst));

//        auto begin_3 = std::chrono::steady_clock::now();
//        Features features;
//        features.calculateFeatures(img, m1, fileName);
//        auto end_3 = std::chrono::steady_clock::now();
//        qDebug() << "Saving features:" << (std::chrono::duration_cast<std::chrono::milliseconds>(end_3 - begin_3)).count() << "ms";

        pr.laplace(m1);
        dst_3 = img;
        m1.to_image(dst_3);
        dst_2 = img;
        for (int i=0;i<img.width();++i) for(int j=0;j<img.height();++j)
            if (dst_3.pixelColor(i,j) == Qt::white)
                dst_2.setPixelColor(i,j,Qt::white);
        dst_2.save(fileName.split(".").at(0) + "_300.jpg", "PNG");

        proc_flag = true;
    }
    else if (!load_flag)
        QMessageBox::information(this, tr("Предупреждение"),tr("Загрузите изображение!"));
    else if (load_flag && proc_flag)
        QMessageBox::information(this, tr("Предупреждение"),tr("Изображение уже обработано!"));
}

void SashaWidget::on_pushButton_3_clicked()
{

}

void SashaWidget::on_pushButton_4_clicked()
{

}

void SashaWidget::on_pushButton_5_clicked()
{

}

void SashaWidget::on_pushButton_6_toggled(bool checked)
{
    if (proc_flag)
    {
        if (checked)
            scene->addPixmap(QPixmap::fromImage(dst_2));
        else
            scene->addPixmap(QPixmap::fromImage(img));
    }
}

void SashaWidget::on_pushButton_6_clicked()
{
    if (!proc_flag && load_flag)
    {
        QMessageBox::information(this, tr("Предупреждение"),tr("Сначала обработайте изображение!"));
        ui->pushButton_6->setChecked(false);
    }
    if (!load_flag && !proc_flag)
    {
        QMessageBox::information(this, tr("Предупреждение"),tr("Загрузите изображение!"));
        ui->pushButton_6->setChecked(false);
    }
}

QString* SashaWidget::getWidgetName()
{
    QString *widgetName = new QString("сашин виджет widget");
    return widgetName;
}
