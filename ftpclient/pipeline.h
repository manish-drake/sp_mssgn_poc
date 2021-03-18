#ifndef PIPELINE_H
#define PIPELINE_H
#include "commandbase.h"
#include <vector>
#include <memory>
#include <QObject>
#include "ftpcontrolchannel.h"
#include "ftpdatachannel.h"

using PipeCmd = std::shared_ptr<CommandBase>;
class Pipeline: public QObject
{
    std::vector<PipeCmd> m_commands;
    FtpControlChannel& m_controlChannel;
    FtpDataChannel &m_dataChannel;
    size_t m_currentIndex;
    PipeCmd *getNextCommand();
    QString m_expextedReply;
    QString getExpectedReply();
public:
    Pipeline(FtpControlChannel &controlChannel, FtpDataChannel &dataChannel, QObject* parent = nullptr);
    Pipeline *Add(const PipeCmd &cmd);
    int Process(const QString &lastReply);
    PipeCmd *at(int index);
};

#endif // PIPELINE_H
