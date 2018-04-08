#include "dilatation.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <ilya/mainwindow.h>
#include <ilya/transformations.h>
#include <ilya/opencvtransform.h>
using namespace std;
using namespace cv;





Mat dilatationOperator(QImage tmp,int dilatation_elem,int dilatation_size)
{
    Mat dilatation_dst;
    int dilatation_type;
    Mat src;
    tmp=tmp.convertToFormat(QImage::Format_RGB32);
    //std::string filename=str.toStdString();
    //src=imread(filename);
    src=ASM::QImageToCvMat(tmp);

    if(dilatation_elem==0){dilatation_type=MORPH_RECT;}
    if(dilatation_elem==1){dilatation_type=MORPH_CROSS;}
    if(dilatation_elem==2){dilatation_type=MORPH_ELLIPSE;}
    Mat element = getStructuringElement(dilatation_type,Size(2*dilatation_size+1,2*dilatation_size+1),Point(dilatation_size,dilatation_size));

    dilate(src,dilatation_dst,element);
    return(dilatation_dst);
    //imwrite("C://Users/llya/Desktop/index.jpg",dilatation_dst);



}
