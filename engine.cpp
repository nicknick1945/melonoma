#include "engine.h"
#include "blackwhitefilte.h"
#include "qlist.h"
#include "contrastfilter.h"
#include "sobelfilter.h"
#include "gaussfilter.h"
#include "medianfilter.h"
#include "otsybinarizer.h"
#include "skiletizationfilter.h"
#include "countvoloscalculater.h"
#include "utils.h"

Engine::Engine()
{
    AbstractFilter *gaussFilter = new GaussFilter();
    AbstractFilter *blackWhiteFilter = new BlackWhiteFilte();
    filters->append(blackWhiteFilter);
    filters->append(gaussFilter);
}


/*
 * Предварительная оработка фотографий фильтрами при загарузке
 */
void Engine::doFilter(QImage &image)
{
    for (int i = 0 ; i < filters->size() ; i ++ ) {
        QString *description = filters->at(i)->getDescription();
        logger->info(*description);
        filters->at(i)->doFilter(image);
    }
}

QImage Engine::doBinary(QImage image,int treshold,bool isInverse)
{
    logger->debug("вход бинаризацию");
    logger->info("порог бинаризации:");
    logger->info(QString::number(treshold));
    return Utils::doBinary(image,treshold,isInverse);
}

void Engine::doFilterPomeh(QImage &image)
{
    mySuperFilter->doFilter(image);   
}

void Engine::doSkiletization(QImage &image)
{
    SkiletizationFilter *skiletizationFilter = new SkiletizationFilter();
    skiletizationFilter->doFilter(image);
}

int Engine::culculateCountVolos(QImage &image)
{
      CountVolosCalculater culculator;
      return culculator.culculateCountVolos(image);
}

double Engine::culculatePersentVolos(QImage &image)
{
    int countVolos = 0 ;
    int countPixels = image.width()*image.height();

   for(int h = 0 ; h < image.height() ; h++){
       for (int w = 0 ; w< image.width() ; w++){
           if(Utils::imImage(w,h,image)&& Utils::getPixelLight(w,h,image)==255){
               countVolos ++;
           }
       }
   }

   return countVolos*100/countPixels;
}
