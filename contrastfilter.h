#ifndef CONTRASTFILTER_H
#define CONTRASTFILTER_H
#include "abstractfilter.h"
#include "qstring.h"

class ContrastFilter : public AbstractFilter{

public:
    ContrastFilter();
    void doFilter(QImage &image);
    QString* getDescription();
};

#endif // CONTRASTFILTER_H
