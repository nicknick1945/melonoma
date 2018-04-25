#include "platform_headers/subprocessmodel.h"

SubProcessModel::SubProcessModel(){}

SubProcessModel::SubProcessModel(DefaultWidget *_widget):DefaultWidgetModel(_widget){}

void SubProcessModel::show()
{
    widget->onLoad();
    widget->show();
}

void SubProcessModel::close()
{
    widget->close();
}
