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

#endif // CACHEFACTORY_H
