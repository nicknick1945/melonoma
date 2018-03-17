#include "kolya_headers/countvoloscalculater.h"
#include "qhash.h"
#include "kolya_headers/utils.h"
#include "QHashIterator"

CountVolosCalculater::CountVolosCalculater(){
}

int CountVolosCalculater::culculateCountVolos(QImage &image)
{
    int countConcov  = stepOne(image);
    return countConcov;
}

int CountVolosCalculater::stepOne(QImage &image)
{
    int countVolos = 0 ;
    for (int h = 0 ; h < image.height() ; h++){
        for (int w = 0 ; w < image.width(); w++){
            if (Utils::imImage(w,h,image)&&Utils::getPixelLight(w,h,image)==255&&haveOnlyOneSosed(w,h,image)){
                countVolos++;
                QString msg = "point:";
                msg.append(" x:");
                msg.append(QString::number(w));
                msg.append(" y:");
                msg.append(QString::number(h));

                QString msg2 = QString("\n").append(QString::number(Utils::getPixelLight(w-1,h-1,image))).append(":")
                    .append(QString::number(Utils::getPixelLight(w,h-1,image))).append(":")
                    .append(QString::number(Utils::getPixelLight(w+1,h-1,image))).append("\n")
                    .append(QString::number(Utils::getPixelLight(w-1,h,image))).append(":")
                    .append(QString::number(Utils::getPixelLight(w,h,image))).append(":")
                    .append(QString::number(Utils::getPixelLight(w+1,h,image))).append("\n")
                    .append(QString::number(Utils::getPixelLight(w-1,h+1,image))).append(":")
                    .append(QString::number(Utils::getPixelLight(w,h+1,image))).append(":")
                    .append(QString::number(Utils::getPixelLight(w+1,h+1,image))).append("\n");

                logger->debug(msg);
                logger->debug(msg2);
            }
        }
    }
    return countVolos/2;
}

int CountVolosCalculater::stepTwo(QImage &image)
{
    QHashIterator<int,int> iter(keysPoint);
    int countVolosWhichHaveKyPoints = 0 ;
    while(iter.hasNext()){
        int x = iter.next().key()%10000;
        int y = iter.next().key()/10000;

        if(haveSosed(x-1,y-1,image)>0)  {
            countVolosWhichHaveKyPoints = countVolosWhichHaveKyPoints + goToNextCoords(x,y,x-1,y-1,image);
        }
        if(haveSosed(x,y-1,image)  >0)  {
            countVolosWhichHaveKyPoints = countVolosWhichHaveKyPoints + goToNextCoords(x,y,x,y-1,image);
        }
        if(haveSosed(x+1,y-1,image)>0)  {
            countVolosWhichHaveKyPoints = countVolosWhichHaveKyPoints + goToNextCoords(x,y,x+1,y-1,image);
        }
        if(haveSosed(x-1,y,image)  >0)  {
            countVolosWhichHaveKyPoints = countVolosWhichHaveKyPoints + goToNextCoords(x,y,x-1,y,image);
        }
        if(haveSosed(x+1,y,image)  >0)  {
            countVolosWhichHaveKyPoints = countVolosWhichHaveKyPoints + goToNextCoords(x,y,x+1,y,image);
        }
        if(haveSosed(x-1,y+1,image)>0)  {
            countVolosWhichHaveKyPoints = countVolosWhichHaveKyPoints + goToNextCoords(x,y,x-1,y+1,image);
        }
        if(haveSosed(x,y+1,image)  >0)  {
            countVolosWhichHaveKyPoints = countVolosWhichHaveKyPoints + goToNextCoords(x,y,x,y+1,image);
        }
        if(haveSosed(x+1,y+1,image)>0)  {
            countVolosWhichHaveKyPoints = countVolosWhichHaveKyPoints + goToNextCoords(x,y,x+1,y+1,image);
        }

    }

    return countVolosWhichHaveKyPoints/2;
}

bool CountVolosCalculater::pointHaveFreeAndMoreSosedov(int x, int y, QImage &image){
    int countSosedov = 0 ;
    countSosedov = countSosedov + haveSosed(x-1,y-1,image);
    countSosedov = countSosedov + haveSosed(x,y-1,image);
    countSosedov = countSosedov + haveSosed(x+1,y-1,image);
    countSosedov = countSosedov + haveSosed(x-1,y,image);
    countSosedov = countSosedov + haveSosed(x+1,y,image);
    countSosedov = countSosedov + haveSosed(x-1,y+1,image);
    countSosedov = countSosedov + haveSosed(x,y+1,image);
    countSosedov = countSosedov + haveSosed(x+1,y+1,image);
    return countSosedov > 2 ;
}


int CountVolosCalculater::culculateKey(int x, int y)
{
    return x + y *10000;
}

bool CountVolosCalculater::containsInKeyPoints(int x, int y)
{
    return keysPoint.contains(culculateKey(x,y));
}

void CountVolosCalculater::addToKeyPoints(int x, int y)
{
    if(!containsInKeyPoints(x,y)){
    keysPoint.insert(culculateKey(x,y),0);
    }
}

int CountVolosCalculater::haveSosed(int x, int y, QImage &image)
{
    if (!Utils::imImage(x,y,image)){
        return 0;
    }else {
        if (image.pixelColor(x,y).blue() == 255){
            return 1;
        } else {
            return 0;
        }
    }
}

int CountVolosCalculater::goToNextCoords(int previousX, int previousY,int x , int y , QImage &image)
{
    if ( !(x-1 == previousX && y-1 == previousY) ){
        if(haveSosed(x-1,y-1,image)  >0){
            if(containsInKeyPoints(x-1,y-1)){
                return 0 ;
            }else{
                return goToNextCoords(x,y,x-1,y-1,image);
            }
        }
    }

    if (!(x == previousX && y-1 == previousY )){
        if(haveSosed(x,y-1,image)  >0){
            if(containsInKeyPoints(x,y-1)){
                return 0 ;
            }else{
                return goToNextCoords(x,y,x,y-1,image);
            }
        }
    }

    if ( !(x+1 == previousX && y-1 == previousY) ){
        if(haveSosed(x+1,y-1,image)  >0){
            if(containsInKeyPoints(x+1,y-1)){
                return 0 ;
            }else{
                return goToNextCoords(x,y,x+1,y-1,image);
            }
        }
    }
    if ( !(x-1 == previousX && y == previousY )){
        if(haveSosed(x-1,y,image)  >0){
            if(containsInKeyPoints(x-1,y)){
                return 0 ;
            }else{
                return goToNextCoords(x,y,x-1,y,image);
            }
        }
    }
    if (!(x+1 == previousX && y == previousY )){
        if(haveSosed(x+1,y,image)  >0){
            if(containsInKeyPoints(x+1,y)){
                return 0 ;
            }else{
                return goToNextCoords(x,y,x+1,y,image);
            }
        }
    }
    if (!(x-1 == previousX && y+1 == previousY )){
        if(haveSosed(x-1,y+1,image)  >0){
            if(containsInKeyPoints(x-1,y+1)){
                return 0 ;
            }else{
                return goToNextCoords(x,y,x-1,y+1,image);
            }
        }
    }
    if (!(x == previousX && y+1 == previousY )){
        if(haveSosed(x,y+1,image)  >0){
            if(containsInKeyPoints(x,y+1)){
                return 0 ;
            }else{
                return goToNextCoords(x,y,x,y+1,image);
            }
        }
    }
    if ( !(x+1 == previousX && y+1 == previousY )){
        if(haveSosed(x+1,y+1,image)  >0){
            if(containsInKeyPoints(x+1,y+1)){
                return 0 ;
            }else{
                return goToNextCoords(x,y,x+1,y+1,image);
            }
        }
    }

    return 1;

}

bool CountVolosCalculater::haveOnlyOneSosed(int x, int y, QImage &image)
{
    int haveSosedov = 0;
    haveSosedov = haveSosed(x-1,y-1,image)
        + haveSosed(x,y-1,image)
        + haveSosed(x+1,y-1,image)
        + haveSosed(x-1,y,image)
        + haveSosed(x+1,y,image)
        + haveSosed(x-1,y+1,image)
        + haveSosed(x,y+1,image)
        + haveSosed(x+1,y+1,image);
    return haveSosedov == 1;
}


