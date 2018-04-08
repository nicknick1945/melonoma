#ifndef DILATATION_H
#define DILATATION_H
#include <QString>
#include <QImage>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
cv::Mat dilatationOperator(QImage tmp,int dilatation_elem, int dilatation_size);




#endif // DILATATION_H
