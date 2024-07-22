#include "logger.h"




Logger::Logger(const QString fileName)
{
    logFile = new QFile();
    logFile->setFileName(fileName);
}

void Logger::log(const QString &msg)
{
    mutex.lock();

    logFile->open(QIODevice::Append | QIODevice::WriteOnly);

    stream.setDevice(logFile);

    QString formattedMsg = QString("%1 | %2 | %3\n").arg(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz")).arg(logFile->fileName()).arg(msg);
    stream << formattedMsg;
    logFile->close();
    mutex.unlock();

}
