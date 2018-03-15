#ifndef BLACKWHITEFILTE_H
#define BLACKWHITEFILTE_H
#include "abstractfilter.h"
#include "loggerfactory.h"
#include "logger.h"

class BlackWhiteFilte :public AbstractFilter
{
public:
    BlackWhiteFilte();
    void doFilter(QImage &image);
    QString* getDescription();
private:
    bool isInverse;
};

#endif // BLACKWHITEFILTE_H
