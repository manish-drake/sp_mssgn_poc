#include "loggerf.h"
#include <ctime>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

static void list_dir(const char *path, std::vector<std::string> & list) {
    struct dirent *entry;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char filename[512] = {0};
        sprintf(filename, "%s/%s", path, entry->d_name);
        list.push_back(filename);
    }

    closedir(dir);
}
LoggerF::LoggerF(): LoggerF("")
{

}
/*!
  @brief Log file is created.
  @param[in] logHead is the log messages contains the state of application.
  @details Log file is created and named as per the current date and time.
*/
LoggerF::LoggerF(const char* logHead, string path):m_appLogFolder{path}
{
    time_t t = time(nullptr);
    tm *ltm = localtime(&t);
    char buffer[32];
    size_t sz = strftime(buffer, 32, "%Y%m%d%H.log", ltm);
    buffer[sz] = '\0';
    if(path.empty())
        m_fp = fopen(buffer, "a");
    else{
        char pathToLog[255] = {};
        sprintf(pathToLog, "%s/%s", path.c_str(), buffer);
        m_fp = fopen(pathToLog, "a");
    }
    this->Log({logHead});
}

void LoggerF::logFiles(std::vector<string> &logList)
{
    list_dir(m_appLogFolder.c_str(), logList);
}


/*!
  @brief Its a de-constructor which closes the file writing.
*/
LoggerF::~LoggerF()
{
    fclose(m_fp);
    delete m_fp;
}
