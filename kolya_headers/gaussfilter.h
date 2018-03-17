#ifndef GAUSSFILTER_H
#define GAUSSFILTER_H
#include "abstractfilter.h"
#include "qstring.h"

class GaussFilter : public AbstractFilter
{
public:
    GaussFilter();
    void doFilter(QImage &image);
    QString * getDescription();
};

#endif // GAUSSFILTER_H
