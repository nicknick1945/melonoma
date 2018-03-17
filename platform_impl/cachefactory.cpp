#include "platform_headers/cachefactory.h"
#include "platform_headers/cache.h"

Cache* CacheFactory::instance = NULL;

CacheFactory::CacheFactory()
{

}

Cache* CacheFactory::getInstance(){
    if (instance == NULL || instance ==0 ){
        instance = new Cache();
    }
    return instance;
}
