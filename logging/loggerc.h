#ifndef LOGGERC_H
#define LOGGERC_H


#include <iostream>
#include "logger.h"

/*!
  @class Functions LoggerC  .
*/
class LoggerC : public Logger
{
    void Log(const std::string &logMsg) override
    {
        std::cout << logMsg << std::endl;
    }
  public:
    LoggerC() = default;
    LoggerC(const char* logHead);
};

#endif // LOGGERC_H
