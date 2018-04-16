#include "platform_headers/defaultwidgetmodel.h"

DefaultWidgetModel::DefaultWidgetModel()
{

}

DefaultWidgetModel::DefaultWidgetModel(DefaultWidget *_widget)
{
    widget = _widget;
}

void DefaultWidgetModel::show()
{
    QString *massege = new QString("запущен виджет:");
    massege->append(widget->getWidgetName());
    logger->info(*massege);
    widget->onLoad();
    widget->show();

}

void DefaultWidgetModel::close()
{
    widget->unlockNextButton();
    widget->preDestroy();
    widget->close();
}

void DefaultWidgetModel::setGeometry(int a, int b, int c, int d)
{
    widget->setGeometry(a,b,c,d);
}
