#include "loggerf.h"
#include <ctime>

LoggerF::LoggerF(): LoggerF("")
{

}
/*!
  @brief Log file is created.
  @param[in] logHead is the log messages contains the state of application.
  @details Log file is created and named as per the current date and time.
*/
LoggerF::LoggerF(const char* logHead)
{
    time_t t = time(nullptr);
    tm *ltm = localtime(&t);
    char buffer[32];
    size_t sz = strftime(buffer, 32, "%Y%m%d%H.log", ltm);
    buffer[sz] = '\0';
    m_fp = fopen(buffer, "a");
    this->Log({logHead});
}


/*!
  @brief Its a de-constructor which closes the file writing.
*/
LoggerF::~LoggerF()
{
    fclose(m_fp);
    delete m_fp;
}
