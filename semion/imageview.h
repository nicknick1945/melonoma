#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H
#include <QGraphicsView>
#include <QWheelEvent>
/*!
 @brief Расширеширение класса QGraphicsView.
 @details Данный класс обеспечивает масштабирование изображения колесиком мыши и навигацию по изображению перетаскиванием (зажатием ПКМ).
 */
class ImageView:public QGraphicsView
{
    Q_OBJECT
public:
    ImageView(QWidget *parent);
    void wheelEvent(QWheelEvent *event);
};

#endif // IMAGEVIEW_H
