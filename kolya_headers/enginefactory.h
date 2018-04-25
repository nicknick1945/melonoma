#ifndef ENGINEFACTORY_H
#define ENGINEFACTORY_H
#include "engine.h"

class EngineFactory
{
public:
    EngineFactory();
private :
    static Engine *instance;
public :
     Engine* getInstance();
};

#endif // ENGINEFACTORY_H
