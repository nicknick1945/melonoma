#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QImage>
#include "ilyawindow.h"


    void magnitude(QImage&,const QImage&,const QImage&);
    QImage convolution(const auto&,const QImage&);
    QImage roberts(const QImage&);
    QImage prewitt(const QImage&);
    QVector<QVector<double>> calculateGaussianKernel(int length, double weight);

#endif // ALGORITHMS_H
