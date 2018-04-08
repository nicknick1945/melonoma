#include "imageview.h"
/*!
 * \brief Конструктор виджета, являющегося потомком parent.
 * \param parent - Указатель на порождающий виджет
 */
ImageView::ImageView(QWidget *parent): QGraphicsView(parent){}
/*!
 * \brief Обработчик событий колеса мышки, обеспечивающий масштабирование сцены.
 * \details Подробнее на QGraphicsView.
 * \param event - Указатель на класс с параметрами события мыши
 */
void ImageView::wheelEvent(QWheelEvent *event)
{
    float delta=event->delta();
    float coef=1+delta/800;
    scale(coef,coef);
    centerOn(mapToScene(event->pos()));
}
