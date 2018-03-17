#include "platform_headers/loggerfactory.h"
#include "platform_headers/logger.h"
#include "iostream"

using namespace std;
LoggerFactory::LoggerFactory(){}


Logger* LoggerFactory::instance = NULL;

Logger* LoggerFactory::getInstance(){
     if (instance == NULL || instance ==0 ){
         instance = new Logger;
     }
     return instance;
}


