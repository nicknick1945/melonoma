#ifndef UTILS_H
#define UTILS_H
#include "qimage.h"
#include "qstring.h"
#include "platform_headers/loggerfactory.h"
#include "platform_headers/logger.h"
#include "vector"
#include "exception"

using namespace std;

class Utils{
  public:
    Utils();
    int WHITE  = 0;
    int BLACK  = 255;
    /**
     * @brief loadImage Функция загружает изображение по заданном путю
     * @param path
     * @return
     */
    static QImage*  loadImage(QString &path){
        QImage *img  =new  QImage();
        LoggerFactory *loggerFactory = new LoggerFactory();
        Logger *logger = loggerFactory->getInstance();
        if(img->load(path)){
            logger->info("изображение успешно загруженно ");
        }else{
            logger->error("ошибка загрузки фотографии");
        }
        return img;
    }


    /**
     * @brief getEmptyDoubleVector создает двойной вектор нужного размера
     * @param width
     * @param height
     * @return
     */
    static vector<vector<int>> getEmptyDoubleVector(int width , int height){
        vector<vector<int>> matrix;
        matrix.resize(height);
        for (int i = 0 ; i < matrix.size() ; i ++){
            matrix.at(i).resize(width);
        }
        return matrix;
    }

    /**
     * @brief toCorrectLight функция отризает значения больше 255 и меньше 0 для того чтобы высталять яркость пикселей
     * @param value
     * @return
     */
    static int toCorrectLight(double value){
        if (value > 255) return 255;
        if(value < 0 ) return 0 ;
        return (int )value;
    }

    /**
     * @brief toCorrectLight функция отризает значения больше 255 и меньше 0 для того чтобы высталять яркость пикселей
     * @param value
     * @return
     */
    static int toCorrectLight(int value){
        if (value > 255) return 255;
        if(value < 0 ) return 0 ;
        return (int )value;
    }

    /**
     * @brief calculeNormalCoords функция для обрезания координат , которые не входят в область значений
     * @param value
     * @param maxCoodrs
     * @return
     */
    static int calculeNormalCoords(int value, int maxCoodrs){
        if(value > (maxCoodrs-1)) return maxCoodrs - 1;
        if(value < 0 ) return 0 ;
        else return value;
    }

    /**
     * @brief getPixelLight получение якрости пикселя , чтобы каждый раз не ебаться с этим
     * @param x
     * @param y
     * @param image
     * @return
     */
    static int getPixelLight(int x, int y , QImage &image){
        return image.pixelColor(x,y).blue();
    }

    /**
     * @brief doBinary функция бинаризации по заданному порогу
     * @param image фотография QImage
     * @param treshold  порог бинаризации
     * @return возращает QImage у которого цвет пикселя по каждой из компонент либо WHITE(255) либо BLACK(0)
     */
    static QImage doBinary(QImage image,int treshold,bool isInverse){
        int imagePixel = isInverse?0:255;
        int noImagePixel =isInverse?255:0 ;
        for(int w = 0 ; w < image.width() ; w++ ){
            for (int h = 0 ; h < image.height(); h ++){
                if(image.pixelColor(w,h).blue() >treshold){
                    image.setPixelColor(w,h,QColor(imagePixel,imagePixel,imagePixel,255));
                }else{
                    image.setPixelColor(w,h,QColor(noImagePixel,noImagePixel,noImagePixel,255));
                }
            }
        }
        return image;
    }
    

    static vector<vector<int>> prepareQImageToBitMap(QImage &image){
        vector<vector<int>> bitMap;
        resizeDoubleVector(bitMap,image.width(),image.height());

        for (int h = 0 ; h < image.height() ; h ++ ){
            for(int w = 0 ; w < image.width() ; w ++ ){
                 bitMap[h][w] = getPixelLight(w,h,image)/255;
            }
        }

        return bitMap;
    }

    static void resizeDoubleVector(vector<vector<int>> &value,int w,int h){
        value.resize(h);
        for(int y = 0 ; y < h ; y++){
            value.at(y).resize(w);
        }
    }

    static void prepareBitMapToQImage(QImage &image,vector<vector<int>> &bitMap){
        for (int h = 0 ; h < image.height() ; h ++ ){
            for(int w = 0 ; w < image.width() ; w ++ ){
                 image.setPixelColor(w,h,QColor(bitMap[h][w],bitMap[h][w],bitMap[h][w],255));
            }
        }
    }

    static bool imImage (int x, int y ,QImage &iamge){
        return (x >= 0 && y >= 0 && x < iamge.width() && y < iamge.height());
    }

};

#endif // UTILS_H
