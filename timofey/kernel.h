#ifndef KERNEL_H
#define KERNEL_H

#include "timofeywindow.h"
#include "haralickfeatures.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

class Kernel: public QObject
{
    Q_OBJECT

public:
    Kernel();
    ~Kernel();

private slots:
    void loadImage();
    void KmeansMethod(QString);
    void saveImage();
    QPixmap makeTransparentImage(QImage&, int);
    QVector<double> calculateFeatures(QImage&);

private:
    TimofeyWindow *timofeyWindow;
    QGraphicsScene *scene;
    QGraphicsScene *scene2;
    QString imagePath;

    QImage defaultImage;
    QImage clusteredImage;
    QImage binaryImage;

};

#endif // KERNEL_H
