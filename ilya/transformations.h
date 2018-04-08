#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include <QImage>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

QImage Mat2QImage(Mat const& src);
Mat QImage2Mat(QImage const& src);


#endif // TRANSFORMATIONS_H
