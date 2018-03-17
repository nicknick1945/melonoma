#include "features.h"

Features::Features():minR(255),meanR(0),maxR(0),
    minG(255),meanG(0),maxG(0),minB(255),meanB(0),maxB(0)
{

}

void Features::calculateFeatures(QImage &orig, ImageMatrix &mask, QString &fileName)
{
    int kx = orig.width()/32;
    int ky = orig.height()/32;
    for (int i=0; i<32; ++i)
        for (int j=0; j<32; ++j)
        {
            int /*r=0,g=0,b=0, */count = 0, th_count=0;
            int k,l;
            minR=minG=minB=minTh=255;
            meanR=meanG=meanB=meanTh=0;
            maxR=maxG=maxB=maxTh=0;
            for (k=0; k<kx; ++k)
                for (l=0; l<ky; ++l)
                {
                    if (mask.get(l+j*ky,k+i*kx) != 0)
                    {
                        /*
                        r = orig.pixelColor(k+i*kx,l+j*ky).red();
                        g = orig.pixelColor(k+i*kx,l+j*ky).green();
                        b = orig.pixelColor(k+i*kx,l+j*ky).blue();
                        minR = std::min(minR, r);
                        meanR += r;
                        maxR = std::max(maxR, r);
                        minG = std::min(minG, g);
                        meanG += g;
                        maxG = std::max(maxG, g);
                        minB = std::min(minB, b);
                        meanB += b;
                        maxB = std::max(maxB, b);
                        ++count; */
                        calculateColors(k+i*kx,l+j*ky, count, orig);
                    }
                    if (mask.get(l+j*ky,k+i*kx) != 0 && ((mask.get(l+j*ky-1,k+i*kx) == 0) || (mask.get(l+j*ky,k+i*kx-1) == 0)))
                    {
                        ++th_count;
                        int h=1, v=1, d=0;
                        int dy = ky-l, dx = kx-k;
                        int q = 1;
                        while (mask.get(l+j*ky+q,k+i*kx) != 0 && dy > 0)
                        {
                            ++v;
                            ++q;
                            --dy;
                        }
                        q=1;
                        while (mask.get(l+j*ky,k+i*kx+q) != 0 && dx > 0)
                        {
                            ++h;
                            ++q;
                            --dx;
                        }
                        d = std::sqrt(h*h+v*v)/2+1;
                        if (d>2*v || d>2*h)
                            d = std::min(v,h);
                        if (d<25)
                        {
                            minTh=std::min(minTh, d);
                            maxTh=std::max(maxTh,d);
                            meanTh+=d;
                        }
                        else
                            --th_count;
                    }
                }
            if (count != 0)
            {
                meanR /= count;
                meanG /= count;
                meanB /= count;
            }
            if (th_count!=0)
                meanTh /= th_count;
            saveFeatures(fileName, k+i*kx, l+j*ky);
        }
}

void Features::saveFeatures(QString &fileName, int x, int y)
{
    QFile file ("features.csv");
    if (!file.open(QIODevice::ReadOnly))
    {
        file.open(QIODevice::Append);
        QTextStream stream(&file);
        stream << "Image,x,y,minR,meanR,maxR,minG,meanG,maxG,minB,meanB,maxB,minTh,meanTh,maxTh";
        file.close();
    }
    file.close();
    file.open(QIODevice::ReadOnly);
    QStringList list, list_name;
    QString str, name;
    QVector <QString> vect_name, vect_i, vect_j;
    list_name = fileName.split("/");
    name = list_name.at(list_name.size()-1);
    QTextStream in(&file);
    str = in.readAll();
    list = str.split("\n");

    for (int i=1; i<list.size(); ++i)
    {
        QString tmp_name = list.at(i).split(",").at(0);
        QString tmp_i = list.at(i).split(",").at(1);
        QString tmp_j = list.at(i).split(",").at(2);
        vect_name.push_back(tmp_name);
        vect_i.push_back(tmp_i);
        vect_j.push_back(tmp_j);
    }
    file.close();
//    if (std::count(vect_name.begin(), vect_name.end(), name) == 0
//            || std::count(vect_i.begin(), vect_i.end(), QString::number(x)) == 0
//            || std::count(vect_j.begin(), vect_j.end(),  QString::number(y)) == 0)
    {
        file.open(QIODevice::Append);
        QTextStream stream(&file);
        stream << "\n"+name+","+QString::number(x)+","+QString::number(y)+","
                  +QString::number(getMinR())+","+QString::number(getMeanR())
                  +","+QString::number(getMaxR())+","+QString::number(getMinG())
                  +","+QString::number(getMeanG())+","+QString::number(getMaxG())
                  +","+QString::number(getMinB())+","+QString::number(getMeanB())
                  +","+QString::number(getMaxB())+","+QString::number(getMinTh())
                  +","+QString::number(getMeanTh())+","+QString::number(getMaxTh());
        file.close();
    }
}

void Features::calculateColors(int x, int y, int &count, QImage &orig)
{
    int r=0,g=0,b=0;
    r = orig.pixelColor(x,y).red();
    g = orig.pixelColor(x,y).green();
    b = orig.pixelColor(x,y).blue();
    minR = std::min(minR, r);
    meanR += r;
    maxR = std::max(maxR, r);
    minG = std::min(minG, g);
    meanG += g;
    maxG = std::max(maxG, g);
    minB = std::min(minB, b);
    meanB += b;
    maxB = std::max(maxB, b);
    ++count;
}
