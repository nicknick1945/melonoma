#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H
#include "qstring.h"
#include "qimage.h"
#include "abstractfilter.h"

class MedianFilter : public AbstractFilter
{
public:
    MedianFilter();
    void doFilter(QImage &image);
    QString* getDescription();
};

#endif // MEDIANFILTER_H
