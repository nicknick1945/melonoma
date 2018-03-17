#include "kolya_headers/mysuperfilter.h"
#include "vector"
#include "kolya_headers/utils.h"
#include "qhash.h"
#include "qlist.h"
using namespace std;

MySuperFilter::MySuperFilter(){}

void MySuperFilter::doFilter(QImage &image){
    objects = new vector<QHash<int ,PixelType>>();
    imageMap.clear();
    int objectsCount = 0 ;
    logger->info("вход в фильтрцию маленьких обьектов"); 
    for (int h = 0 ; h < image.height() ; h ++ ){
        for (int w = 0 ; w < image.width() ; w++){
            if (Utils::getPixelLight(w,h,image) == WHITE && !contains(w,h,imageMap) ){
                findArea(w,h,image);
                objectsCount++;
            }
        }
    }
    logger->debug("найденно обьектиков:");
    logger->debug(QString::number(objectsCount));
    prepareResultsToImage(image);
    delete objects;

}

void MySuperFilter::findArea(int startX, int startY, QImage &image){
    QHash<int,PixelType> currentAreaMap;
    findAreaRecursive(startX,startY,currentAreaMap,image);
    QHashIterator<int,PixelType> iter(currentAreaMap);
    QString msg = "размер обьектика : ";
    msg.append(QString::number(currentAreaMap.size()));
    logger->debug(msg);

    if(currentAreaMap.size()>50){
        objects->push_back(currentAreaMap);
        while(iter.hasNext()){
            iter.next();
            imageMap.insert(iter.key(),PixelType::OBJECT) ;
        }
    }else{
        while(iter.hasNext()){
            iter.next();
            imageMap.insert(iter.key(),PixelType::NO_OBJECT) ;
        }
    }
    currentAreaMap.clear();
}

void MySuperFilter::findAreaRecursive(int startX, int startY, QHash<int,PixelType> &currentAreaMap,QImage &image){
    currentAreaMap.insert(culculateKey(startX,startY),PixelType::NO_OBJECT);
    if (inImageAndNoJustContaintAndWhite(startX+1,startY,currentAreaMap,image)) findAreaRecursive(startX+1,startY,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX-1,startY,currentAreaMap,image)) findAreaRecursive(startX-1,startY,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX,startY-1,currentAreaMap,image)) findAreaRecursive(startX,startY-1,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX,startY+1,currentAreaMap,image)) findAreaRecursive(startX,startY+1,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX-1,startY-1,currentAreaMap,image)) findAreaRecursive(startX-1,startY-1,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX-1,startY+1,currentAreaMap,image)) findAreaRecursive(startX-1,startY+1,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX+1,startY-1,currentAreaMap,image)) findAreaRecursive(startX+1,startY-1,currentAreaMap,image);
    if (inImageAndNoJustContaintAndWhite(startX+1,startY+1,currentAreaMap,image)) findAreaRecursive(startX+1,startY+1,currentAreaMap,image);
}



void MySuperFilter::prepareResultsToImage(QImage &image)
{
    clearImage(image);
    //skiletization();
    for (int count = 0 ; count < objects->size() ; count++){
        QHashIterator<int,PixelType> iter(objects->at(count));
        while(iter.hasNext()){
            iter.next();
            int coordX = iter.key()%10000;
            int coordY = iter.key()/10000;
            image.setPixelColor(coordX,coordY,QColor(WHITE,WHITE,WHITE,255));
        }
    }

}

void MySuperFilter::skiletization()
{
    QString msg = "найдено обьектов";
    msg.append(QString::number(objects->size()));
    logger->info(msg);
    for (int count = 0 ; count < objects->size(); count++){
        int countDeletedPixels = 0;
        do{
            Coords startCoodrs = findBugSturtCooddinate(objects->at(count));
            countDeletedPixels = oneCircleIteratoin(count, startCoodrs);
            }while(countDeletedPixels>0);
    }
}


int MySuperFilter::oneCircleIteratoin(int count, Coords &startCoodrsNew){

    Coords currentCoordsNew(startCoodrsNew.getX(),startCoodrsNew.getY());
    QList<int> keysToDeleteFromArea;
    Course course = RIGHT;
    do {
        resolvToDelete(objects->at(count),keysToDeleteFromArea,currentCoordsNew,course);
        switch (course) {

            case RIGHT:{
                if (contains(currentCoordsNew,0,1,objects->at(count))){
                    if(!contains(currentCoordsNew,1,0,objects->at(count))){
                        course = Course::RIGHT;
                        currentCoordsNew.setX(currentCoordsNew.getX()+1);
                    }else if(!contains(currentCoordsNew,0,-1,objects->at(count))){
                            course =Course::UP;
                            currentCoordsNew.setY(currentCoordsNew.getY()-1);
                    }else {
                            course =  brickDeadLock(course);
                    }
                }else  {
                        course = Course::DOWN;
                        currentCoordsNew.setY(currentCoordsNew.getY()+1);
                    }
                    break;
                }
                case LEFT:{

                    if (contains(currentCoordsNew,0,-1,objects->at(count))){
                        if(!contains(currentCoordsNew,-1,0,objects->at(count))){
                            course = Course::LEFT;
                            currentCoordsNew.setX(currentCoordsNew.getX()-1);;
                        }else if(!contains(currentCoordsNew,0,1,objects->at(count))){
                            course = Course::DOWN;
                            currentCoordsNew.setY(currentCoordsNew.getY()+1);
                        }else {
                            course = brickDeadLock(course);
                        }
                    }else  {
                        course = Course::UP;
                        currentCoordsNew.setY(currentCoordsNew.getY()-1);
                    }
                    break;
                }
                case UP:{
                    if (contains(currentCoordsNew,+1,0,objects->at(count))){
                        if(!contains(currentCoordsNew,0,-1,objects->at(count))){
                            course = Course::UP;
                            currentCoordsNew.setY(currentCoordsNew.getY()-1);
                        }else if(!contains(currentCoordsNew,-1,0,objects->at(count))){
                            course = Course::LEFT;
                            currentCoordsNew.setX(currentCoordsNew.getX()-1);
                        }else {
                            course = brickDeadLock(course);
                        }
                    }else  {
                        course = Course::RIGHT;
                        currentCoordsNew.setX(currentCoordsNew.getX()+1);
                    }
                    break;

                }
                case DOWN:{
                    if (contains(currentCoordsNew,-1,0,objects->at(count))){
                        if(!contains(currentCoordsNew,0,1,objects->at(count))){
                            course = Course::DOWN;
                            currentCoordsNew.setY(currentCoordsNew.getY()+1);
                        }else if(!contains(currentCoordsNew,1,0,objects->at(count))){
                            course = Course::RIGHT;
                            currentCoordsNew.setX(currentCoordsNew.getX()+1);
                        }else {
                            course = brickDeadLock(course);
                        }
                    }else  {
                        course = Course::LEFT;
                        currentCoordsNew.setX(currentCoordsNew.getX()-1);
                    }
                    break;

                }
        }
    }while(!isFinished(startCoodrsNew,currentCoordsNew));

    for (int i = 0 ; i < keysToDeleteFromArea.size(); i++){
        objects->at(count).remove(keysToDeleteFromArea.at(i));
    }

    logger->info("решено удалить :");
    logger->info(QString::number(keysToDeleteFromArea.size()));
    return keysToDeleteFromArea.size();
}

void MySuperFilter::resolvToDelete(const QHash<int, PixelType> &object, QList<int> &listToDelete, Coords &currentCoords, Course cource)
{
    //условия тут пиздец какие сложные да же описывать не буду :)
    switch (cource) {
        case UP:{
            if(contains(currentCoords,1,0,object)
                    && contains(currentCoords,2,0,object)
                    && !listToDelete.contains(culculateKey(currentCoords.getX()+2,currentCoords.getY()))
              //      && (contains(currentCoords,1,1,object)|| contains(currentCoords,1,-1,object) )
                    ){
                if(!contains(currentCoords,0,1,object)
                        || listToDelete.contains(culculateKey(currentCoords.getX(), currentCoords.getY()+1)) ){

                    if(!contains(currentCoords,0,-1,object) && !listToDelete.contains(culculateKey(currentCoords.getX()+1,currentCoords.getY()+1))){
                            listToDelete.append(culculateKey(currentCoords.getX()+1,currentCoords.getY()));
                    }else{
                        if(contains(currentCoords,1,-1,object) && !listToDelete.contains(culculateKey(currentCoords.getX()+1,currentCoords.getY()-1))){
                            listToDelete.append(culculateKey(currentCoords.getX()+1,currentCoords.getY()));
                        }
                    }
                }
            }
            break;
        }
        case DOWN:{
            if(contains(currentCoords,-1,0,object)
                    && contains(currentCoords,-2,0,object)
                    && !listToDelete.contains(culculateKey(currentCoords.getX()-2,currentCoords.getY()))
                   // && ( contains(currentCoords,-1,1,object)|| contains(currentCoords,-1,-1,object) )
                    ){
                if(!contains(currentCoords,0,1,object)
                        || listToDelete.contains(culculateKey(currentCoords.getX(), currentCoords.getY()+1)) ){
                    if(!contains(currentCoords,0,+1,object) && !listToDelete.contains(culculateKey(currentCoords.getX()-1,currentCoords.getY()-1))){
                            listToDelete.append(culculateKey(currentCoords.getX()-1,currentCoords.getY()));
                    }else{
                        if(contains(currentCoords,-1,+1,object) && !listToDelete.contains(culculateKey(currentCoords.getX()-1,currentCoords.getY()+1))){
                            listToDelete.append(culculateKey(currentCoords.getX()-1,currentCoords.getY()));
                        }
                    }
                }
            }
            break;
        }
        case LEFT:{
            if(contains(currentCoords,0,-1,object)
                    && contains(currentCoords,0,-2,object)
                    && !listToDelete.contains(culculateKey(currentCoords.getX(),currentCoords.getY()-2))
                 //   && ( contains(currentCoords,-1,-1,object)|| contains(currentCoords,1,-1,object) )
                    ){
                if(!contains(currentCoords,1,0,object)
                        || listToDelete.contains(culculateKey(currentCoords.getX()+1, currentCoords.getY()))){
                    if(!contains(currentCoords,-1,0,object) && !listToDelete.contains(culculateKey(currentCoords.getX()+1,currentCoords.getY()-1))){
                            listToDelete.append(culculateKey(currentCoords.getX(),currentCoords.getY()-1));
                    }else{
                        if(contains(currentCoords,-1,-1,object) && !listToDelete.contains(culculateKey(currentCoords.getX()-1,currentCoords.getY()-1))){
                            listToDelete.append(culculateKey(currentCoords.getX(),currentCoords.getY()-1));
                        }
                    }
                }
            }
            break;
        }
        case RIGHT:{
            if(contains(currentCoords,0,1,object)
                    && contains(currentCoords,0,2,object)
                    && !listToDelete.contains(culculateKey(currentCoords.getX(),currentCoords.getY()+2))
                //    && ( contains(currentCoords,1,1,object)|| contains(currentCoords,-1,1,object) )
                    ){
                if(!contains(currentCoords,-1,0,object)
                        || listToDelete.contains(culculateKey(currentCoords.getX()-1, currentCoords.getY()))){

                    if(!contains(currentCoords,1,0,object) && !listToDelete.contains(culculateKey(currentCoords.getX()-1,currentCoords.getY()+1))){
                        listToDelete.append(culculateKey(currentCoords.getX(),currentCoords.getY()+1));
                    }else{
                        if(contains(currentCoords,1,1,object) && !listToDelete.contains(culculateKey(currentCoords.getX()+1,currentCoords.getY()+1)) ){
                            listToDelete.append(culculateKey(currentCoords.getX(),currentCoords.getY()+1));
                        }
                    }
                }
            }
            break;
        }
    }
}


Coords MySuperFilter::findBugSturtCooddinate(const QHash<int, PixelType> &currentArea)
{

    QHashIterator<int,PixelType> iter(currentArea);
    int minY =10000;
    int minX = 0 ;
    while(iter.hasNext()){
        iter.next();        
        if(iter.key()/10000 < minY){
            minY = iter.key()/10000;
            minX = iter.key()%10000;
        }
    }

    /*
     * -1 так как в качестве стратовой точки я возьму точку над крайним
     * верхним левым пикселем донного изображения
     */
    return Coords(minX,minY-1);
}

void MySuperFilter::putInImageMap(int x, int y , PixelType pixelType){
    imageMap.insert(culculateKey(x,y),pixelType);
}

bool MySuperFilter::contains(int x, int y,QHash<int,PixelType> &currentMap){
    return currentMap.contains(culculateKey(x,y));
}

QString *MySuperFilter::getDescription(){
    QString *description = new QString("мой фильтр для убирания помех");
    return description;
}

Course MySuperFilter::brickDeadLock(Course course)
{
    switch (course){
    case RIGHT:{
        return Course::LEFT;
        break;
    }
    case LEFT:{
        return Course::RIGHT;
        break;
    }
    case UP:{
        return Course::DOWN;
        break;

    }
    case DOWN:{
        return Course::UP;
        break;
    }

    }
}

bool MySuperFilter::isFinished(Coords &startCoords, Coords &currentCoords)
{
    return startCoords.getX()==currentCoords.getX() && startCoords.getY() == currentCoords.getY();
}

bool MySuperFilter::contains(Coords &coords, int shiftX, int shiftY,const QHash<int,PixelType> &object)
{
    if (coords.getY() + shiftY < 0 ) return false;
    if (coords.getX() + shiftX < 0 ) return false;
    return object.contains(culculateKey(coords.getX()+shiftX,coords.getY()+shiftY));
}

bool MySuperFilter::inImage( int x, int y,QImage &image){
    return x >= 0 && x <= (image.width() - 1 ) && y >=0 && y <= (image.height() -1 );
}

int MySuperFilter::culculateKey(int x, int y){
    return x+y*10000 ;
}

bool MySuperFilter::inImageAndNoJustContaintAndWhite(int x, int y, QHash<int,PixelType> &currentArea, QImage &image){
    return  inImage(x,y,image)&&(!contains(x,y,currentArea))&&(Utils::getPixelLight(x,y,image) == WHITE);
}

void MySuperFilter::clearImage(QImage &image){
    for (int h = 0 ; h < image.height() ; h ++){
         for (int w = 0 ; w  <image.width() ; w++){
             image.setPixelColor(w,h,QColor(BLACK,BLACK,BLACK,255));
         }
    }
}
