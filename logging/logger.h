#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>


using namespace std;


enum Level
{
    Info,
    Warn,
    Err
};
inline std::string methodName(const std::string& prettyFunction)
{
    size_t colons = prettyFunction.find("::");
    size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
    size_t end = prettyFunction.rfind("(") - begin;

    return prettyFunction.substr(begin,end);
}

#define METHOD_NAME methodName(__PRETTY_FUNCTION__)
#define LOGINFO(info) (Logger::Instance()->Log(Level::Info, METHOD_NAME.c_str(), (info)))
#define LOGINFOZ(fmt, ...) (Logger::Instance()->Log(Level::Info, METHOD_NAME.c_str(), (fmt), __VA_ARGS__))
#define LOGWARN(warn) (Logger::Instance()->Log(Level::Warn, __func__, (warn)))
#define LOGWARNZ(warn, ...) (Logger::Instance()->Log(Level::Warn, __func__, (warn), __VA_ARGS__))
#define LOGERR(err) (Logger::Instance()->Log(Level::Err, __func__, (err)))
#define LOGERRZ(err, ...) (Logger::Instance()->Log(Level::Err, __func__, (err), __VA_ARGS__))

#define UNUSED(x) (void)(x)
class FileLogger;


/*!
  @class Functions Log, Add writes log values in the file/console , Log .
*/
class Logger
{
    static Logger *s_logger;
    static void setLoggers(Logger* sLogger)
    {
        sLogger->m_logMod =   getenv("LOG_MOD");
        const char* logLvl= getenv("LOG_LVL");
        if(logLvl)
            sLogger->m_logLvl = atoi(logLvl);
    }

    std::vector<Logger*> m_loggers;
    int m_logLvl;
    const char* m_logMod;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
protected:
    Logger()=default;
    ~Logger();

public:
    virtual void Log(const std::string &logMsg);
    static Logger *Instance()
    {
        if (!s_logger)
        {
            s_logger = new Logger;
            setLoggers(s_logger);
        }
        return s_logger;
    }
    void Add(Logger* logger);
    void Log(Level level, const char *module, const std::string &logMsg);
    void Log(Level level, char const *module, char const *fmt, ...);

    template<class CAST>
    CAST* cast()
    {
        CAST* ret = nullptr;
        auto c = typeid (CAST).name();
        for(auto &logger:m_loggers)
        {
            auto l = typeid (*logger).name();
            if( l == c )
            {
                ret = static_cast<CAST*>(logger);
                break;
            }
        }

        return ret;
    }
};

#endif // LOGGER_H
