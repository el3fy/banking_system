#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QMutex>
#include <QTextStream>
#include <QMap>

class Logger
{
public:
    Logger(const QString fileName);
    void log(const QString &msg);

private:
    QString msg;
    QFile *logFile;
    QTextStream stream;
    QMutex mutex;

};

#endif // LOGGER_H
