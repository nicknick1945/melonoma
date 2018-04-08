#include "algorithms.h"
#include <QtWidgets>
#include <cmath>
#include <utility>
#include <queue>
#include <QImage>
#include "kernels.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <stdlib.h>


using namespace cv;
using namespace std;


void magnitude(QImage& input,const QImage& gx,const QImage& gy)
{
    quint8 *line;
    const quint8 *gx_line,*gy_line;

    for(int y=0;y<input.height();y++)
    {
        line=input.scanLine(y);
        gx_line=gx.constScanLine(y);
        gy_line=gy.constScanLine(y);
        for(int x=0;x<input.width();x++)
        {
            line[x]=qBound(0x00,static_cast<int>(hypot(gx_line[x],gy_line[x])),0xFF);
        }

    }

}

QImage convolution(const auto& kernel,const QImage& image)
{
    int kw=kernel[0].size();
    int kh=kernel.size();
    int offsetx=kw/2;
    int offsety=kw/2;
    QImage out(image.size(),image.format());
    float sum;
    quint8 *line;
    const quint8 *lookup_line;

    for(int y=0;y<image.height();y++)
    {
        line=out.scanLine(y);
        for(int x=0;x<image.width();x++)
        {
            sum=0;
             for(int j=0;j<kh;j++)
            {
                if(y+j<offsety || y+j >=image.height())
                {
                    continue;
                }
                lookup_line=image.constScanLine(y+j-offsety);
                for(int i=0;i<kw;i++)
                {
                    if(x+i<offsetx || x+i >=image.width())
                    {
                        continue;
                    }
                    sum+=kernel[j][i]*lookup_line[x+i-offsetx];
                }

             }
             line[x]=qBound(0x00,static_cast<int>(sum),0xFF);
        }


    }

    return out;

}


QImage roberts(const QImage& input)
{
    QImage res(input.size(),input.format());
    magnitude(res,convolution(robertsx,input),convolution(robertsy,input));
    return res;
}

QImage prewitt(const QImage& input) {
    QImage res(input.size(), input.format());
    magnitude(res, convolution(prewittx, input), convolution(prewitty, input));
    return res;
}

