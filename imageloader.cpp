#include "qstring.h"
#include "qimage.h"


public static QImage loadImageByPath(QString &path){
    QImage image = QImage.load(path);
    return image;
}
