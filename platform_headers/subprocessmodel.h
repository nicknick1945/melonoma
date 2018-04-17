#ifndef SUBPROCESSMODEL_H
#define SUBPROCESSMODEL_H

#include "defaultwidgetmodel.h"

class SubProcessModel: public DefaultWidgetModel
{
public:
    SubProcessModel();
    SubProcessModel(DefaultWidget * _widget);
    void show();
    void close();
};

#endif // SUBPROCESSMODEL_H
