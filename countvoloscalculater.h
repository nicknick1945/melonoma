#ifndef COUNTVOLOSCALCULATER_H
#define COUNTVOLOSCALCULATER_H
#include "logger.h"
#include "loggerfactory.h"
#include "qimage.h"
#include"qhash.h"

/**
 * @brief The CountVolosCalculater class
 * класс для подсчета колличества волос на бинаризованном скилетезированном изображении
 * в других случаях идите не тыкайте а эту сука блэт кнопку иначе пердец
 */
class CountVolosCalculater
{
public:
    CountVolosCalculater();
    int culculateCountVolos(QImage &image);
private:
    LoggerFactory *loggerFactory = new LoggerFactory();
    Logger *logger = loggerFactory->getInstance();
    /**
     * @brief stepOne Функция предназначена для поиска ключевых точек
     * это те точки , которые имеют больше 1-го соседа
     */
    QHash<int,int> keysPoint;
    int stepOne(QImage &image);
    int stepTwo(QImage &image);
    bool pointHaveFreeAndMoreSosedov(int x ,int y,QImage &image);
    int culculateKey(int x,int y );
    bool containsInKeyPoints(int x,int y);
    void addToKeyPoints(int x, int y);
    bool inImage(int x,int y,QImage &iamge);
    int haveSosed(int x , int y , QImage &image);
    int goToNextCoords(int previousX,int previousY,int x , int y ,QImage &image);
    bool haveOnlyOneSosed(int x, int y , QImage &image);

};

#endif // COUNTVOLOSCALCULATER_H
