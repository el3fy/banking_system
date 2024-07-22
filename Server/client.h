#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QEventLoop>
#include <QThread>
#include "logger.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "request.h"

class Client : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Client(qintptr socketDescriptor = 0, QObject *parent = nullptr);

private:
    qintptr m_socketDescriptor;
    QTcpSocket *socket;
    Logger *ClientLogs;
    Request *l_handler;

private slots:
    void disconnected();
    void readyRead();

    // QRunnable interface
public:
    void run() Q_DECL_OVERRIDE;
};



#endif // CLIENT_H
