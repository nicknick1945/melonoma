#include "platform_headers/logger.h"
#include "iostream"
#include "qstringlist.h"
#include "QFile"
#include "QTextStream"
#include "QTime"
using namespace std;

Logger::Logger()
{

}

void Logger::info(QString message)
{
    LogLevel logLevel = getLogLevel();
    if ( logLevel != LogLevel::DEBUG ){
        cout<<getTime().toStdString()<<" "<<"INFO:"<<message.toStdString()<<endl;
    }
}

void Logger::debug(QString message){
    LogLevel logLevel = getLogLevel();
    if ( logLevel != LogLevel::INFO){
        cout<<getTime().toStdString()<<" "<<"DEBUG:"<<message.toStdString()<<endl;
    }
}

void Logger::error(QString message){
    cout<<getTime().toStdString()<<" "<<"ERROR:"<<message.toStdString()<<endl;
}

QString Logger::getTime()
{
    QDateTime dateTime = dateTime.currentDateTime();
    QString dateTimeString = dateTime.toString("yyyy-MM-dd hh:mm:ss");
    return dateTimeString;
}

LogLevel Logger::getLogLevel()
{
    if(workRegim==LOAD_ON_START && !firstStart){
        return logLevell;
    } else if(workRegim==LOAD_BY_MASSEG){
        QString line;
        QFile logLevel("logLevel.txt");// обьявляем
        if (!logLevel.open(QIODevice::ReadOnly | QIODevice::Text)){// открываем
            cout<<"can't open logLevel"<<endl;//на всякий случай
            return LogLevel::INFO;
        }
        QTextStream accIn(&logLevel), lineIn(&line);// первый - стрим файла, второй - читаемой строки
        line = accIn.readLine();
        QStringList property = line.split("=");
        if(property.at(1).contains("debug")){
            return LogLevel::DEBUG;
        }else if (property.at(1).contains("info")){
            return LogLevel::INFO;
        }else if (property.at(1).contains("error")){
            return LogLevel::ERROR;
        }
        logLevel.close();
        firstStart = false;
        return LogLevel::INFO;
    }
    else{
        return logLevell;
    }
}
