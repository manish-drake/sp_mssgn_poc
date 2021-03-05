#include "loggerc.h"

/*!
  @brief Its a paramterised constructor which displays state of application in console as logs .
  @param[in] logHead is the log messages contains the state of application.
*/
LoggerC::LoggerC(const char* logHead)
{
    this->Log({logHead});
}
