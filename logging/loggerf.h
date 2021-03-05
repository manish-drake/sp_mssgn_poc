#ifndef LOGGERF_H
#define LOGGERF_H


#include "logger.h"
#include <fstream>

/*!
  @class Functions LoggerF .
*/
class LoggerF : public Logger
{
    void Log(const std::string &logMsg) override
    {
        fprintf(m_fp, "%s\n", logMsg.c_str());
        fflush(m_fp);
    }
    FILE *m_fp;
  public:
    LoggerF();
    LoggerF(const char* logHead);
    ~LoggerF();
};

#endif // LOGGERF_H
