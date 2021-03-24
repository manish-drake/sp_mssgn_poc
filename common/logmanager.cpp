#include "logmanager.h"
#include "loggerf.h"
#include "ftp.h"
#include <QFileInfo>
#include <QDir>

QString LogManager::filterName(const QString &filename)
{
    QString name;
    int pos = filename.lastIndexOf("/");
    if(pos >= 0)
    {
        name = filename.right(filename.size() - pos - 1);
    }
    return name;
}
QStringList LogManager::getLogs()
{
    std::vector<std::string> logList;
    QStringList names;
    LoggerF* fLogger = Logger::Instance()->cast<LoggerF>();
    m_logFiles.clear();
    if(fLogger)
    {
        fLogger->logFiles(logList);

        for(int nIter=0; nIter < logList.size(); nIter++)
        {
            QString filename = QString::fromStdString(logList[nIter]);

            QString name = filterName(filename);
            if(!name.startsWith("."))
            {
                m_logFiles.insert(name, filename);
                names << name;
            }
        }
    }

    return names;
}

LogManager::LogManager(QObject *parent) : QObject(parent)
{
    auto names = getLogs();
    m_interfaces.setStringList(names);
    emit interfacesChanged();
}

void LogManager::refresh()
{
    auto names = getLogs();
    m_interfaces.setStringList(names);
    emit interfacesChanged();
}

void LogManager::ftp()
{
    for(auto &filename: m_logFiles.values())
    {
        ftp_t ftp(m_serverIP.toStdString().c_str(), 21);
        ftp.login("sportspip", "drake8283");

        QFileInfo fInfo(filename);
        QString bname = fInfo.baseName();
        QString fname = bname.append(".").append(fInfo.completeSuffix());

        size_t szFile = ftp.put_file(filename.toStdString().c_str(), fname.toStdString().c_str());
        QFile::remove(filename);
    }
    refresh();
}

void LogManager::clean()
{

}

void LogManager::ftpServerNotified(QString serverIP)
{
    m_serverIP = serverIP;
}
