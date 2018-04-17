#include "kolya_headers/enginefactory.h"


using namespace std;
EngineFactory::EngineFactory(){}


Engine* EngineFactory::instance = NULL;

Engine* EngineFactory::getInstance(){
     if (instance == NULL || instance ==0 ){
         instance = new Engine;
     }
     return instance;
}
