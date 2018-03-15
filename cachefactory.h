#ifndef CACHEFACTORY_H
#define CACHEFACTORY_H
#include "cache.h"


class CacheFactory
{
public:
    CacheFactory();
private :
    static Cache *instance;
public :
     Cache* getInstance();
};

/*
 * class Logger;

class LoggerFactory
{
public:
    LoggerFactory();
private :
    static Logger* instance;

public :
    Logger* getInstance();
};

 * */

#endif // CACHEFACTORY_H
