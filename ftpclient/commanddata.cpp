#include "commanddata.h"
#include "ftpcontrolchannel.h"
#include "ftpdatachannel.h"
#include <QFile>

CommandData::CommandData(const std::string &file):CommandBase{""}
{
    this->setArgs(file);
    this->setReply("reply.2xx");
}

int CommandData::Run(FtpControlChannel &controlCHannel, FtpDataChannel &dataChannel)
{
    int result = 0;

    QFile file(QString::fromStdString(this->args()));

    if (!file.open(QIODevice::ReadOnly))
        return -1;

    QByteArray blob = file.readAll();
    dataChannel.sendData(blob);
    dataChannel.close();

    return result;
}
