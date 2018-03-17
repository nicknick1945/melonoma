#ifndef MYSUPERFILTER_H
#define MYSUPERFILTER_H
#include "abstractfilter.h"
#include "qhash.h"
#include "qlist.h"
#include "coords.h"
/**
 * @brief The MySuperFilter class
 * фильтр предназначенный для убирания помех на бинаризованном изображении
 * он убирает с изображения маленькие обькты , размером меньше чем 40 пикселов
 */
using namespace std;

enum PixelType{

    NO_OBJECT,OBJECT
};

enum Course{
    RIGHT,LEFT,UP,DOWN
};

class MySuperFilter : public AbstractFilter
{
public:
    MySuperFilter();


    virtual void doFilter(QImage &image) ;
    virtual QString* getDescription();  


private:
    /**
     * @brief map
     * короче прикол в том , что в этом фильтре мы будем проходить по изображению и
     * рекусиво выделять каждый обект который белый ну и соответственно если он меньше 40
     * пикселей удалять его , но в то же время мы не должны дваджы проходить по одному и тому же месту
     * что очень бы замедлило процесс
     * поэтому создадим карту , в которую будем добавлять пиксели , которые мы уже проходили и считали обектами
     * чтобы все это быстро работало , будем из добавлять в эту карту с пометками
     * NO_RECOGNIZED,NO_OBJECT,OBJECT
     * чтобы пару  х, у мы могли однозначно описать одним числом , будем вписывать туда одно число
     * которое будет ровняться у*10000 + х ; таким образом на изображения накладывается ограниение в размере
     * по координате х до 9999 пикселов
     */
    QHash<int,PixelType> imageMap;
    vector<QHash<int,PixelType>> *objects;
    int BLACK = 0;
    int WHITE = 255;
    Course brickDeadLock(Course course);
    bool isFinished(Coords &startCoords,Coords &currentCoords);
    bool contains(Coords &coodrs , int shiftX,int shiftY,const QHash<int,PixelType> &object);
    bool contains(int x, int y,QHash<int,PixelType> &currentMap);
    void putInImageMap(int x, int y,PixelType pixelType);
    void findArea(int stratX, int startY ,QImage &image);
    void findAreaRecursive(int stratX, int startY ,QHash<int,PixelType> &currentAreaQHash,QImage &image);
    int culculateKey(int x , int y );
    bool inImageAndNoJustContaintAndWhite(int x, int y ,QHash<int,PixelType> &currentArea ,QImage &image);
    /**
     * @brief inImage функция определяет принадлежит ли точка изображению
     * @param image
     * @param x
     * @param y
     * @return
     */
    bool inImage(int x,int y,QImage &image);
    /**
     * применить все полученные штуки к изображению
     * @brief prepareResultsToImage
     * @param image
     */
    void prepareResultsToImage(QImage &image);
    /**
     * мой самописный алгоритм скилетизиции , основан на том,
     * что жук бегает вокруг границы изображения и помечает пиксели слева от
     * напрвления движения , которые имеют соседа слева , как пиксели на удаление
     * как только жук завершает круг, помеченные пиксели удаляются
     * действия повторяются до тез пор пока за круг не будет не помечено ни одного пикселя
     * @brief skiletization
     */
    void skiletization();
    /**
     * ФУнкция которая определяет удалять ли пиксель при скелетезации
     * @brief resolvToDelete
     * @param object   обьект в виде набора координат HashMap
     * @param listToDelete  список в который буудет внесен пиксель в случае , если его нужно удалить
     * @param currentCoords текущая координата
     * @param cource направление в котором сейчас происходит обход
     */
    void resolvToDelete(const QHash<int,PixelType> &object,QList<int> &listToDelete,Coords &currentCoords,Course cource);
    /**
     *Один цикл обхода обьекта в уелях удаления краевыз пикселей
     * @brief oneCircleIteratoin
     * @param count номер обьекта в списке обьектов
     * @param startCoodrs координата старта обхода
     * @return ничего не возвращает
     */
    int oneCircleIteratoin(int count, Coords &startCoodrs);
    /**
     * @brief findBugSturtCooddinate поиск координат начала обхода (выбирается нижняя точка)
     * @param currentArea выбраный обьект
     * @return воздращает координаты в виде 10000*у + x
     */
    Coords findBugSturtCooddinate(const QHash<int,PixelType> &currentArea);

    /** Функция отчистки изображения просто делает картинку черной
     * @brief clearImage
     * @param image
     */
    void clearImage(QImage &image);
};

#endif // MYSUPERFILTER_H
