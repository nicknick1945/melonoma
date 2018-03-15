#ifndef LOGGER_H
#define LOGGER_H
#include "qstring.h"

enum LogLevel {
INFO ,DEBUG ,ERROR
};

enum WorkRegim{
    LOAD_BY_MASSEG,LOAD_ON_START
};

class Logger
{
public:
    Logger();
    void info(QString messege);
    void debug(QString messege);
    void error(QString messege);
private :
   bool firstStart = true;
   LogLevel logLevell = LogLevel::INFO;
   QString getTime();
   WorkRegim workRegim=WorkRegim::LOAD_ON_START;
   LogLevel getLogLevel();


};


#endif // LOGGER_H
