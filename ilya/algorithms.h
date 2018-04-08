#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <QImage>
//#include "mainwindow.h"
    void magnitude(QImage&,const QImage&,const QImage&);
    QImage convolution(const auto&,const QImage&);
    QImage roberts(const QImage&);
    QImage prewitt(const QImage&);

#endif // ALGORITHMS_H
