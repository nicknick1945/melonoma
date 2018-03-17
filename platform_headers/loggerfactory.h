#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H
#include "logger.h"

class Logger;

class LoggerFactory
{
public:
    LoggerFactory();
private :
    static Logger* instance;

public :
    Logger* getInstance();
};

#endif // LOGGERFACTORY_H
