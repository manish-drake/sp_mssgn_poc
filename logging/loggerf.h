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
    std::string m_appLogFolder;
  public:
    LoggerF();
    LoggerF(const char* logHead, string path = "");

    void logFiles(std::vector<std::string> &logList);

    ~LoggerF();
};

#endif // LOGGERF_H
