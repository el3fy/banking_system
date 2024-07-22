#include "server.h"

Server::Server(QObject *parent)
    : QTcpServer{parent}
{
    qInfo()<<"db server"<< &(Database::getInstance()); //getting instance of Database(singleton).
    pool = new QThreadPool(this);
    pool->setMaxThreadCount(200);

    ServerLogs = new Logger("./serverLogs");
}

Server::~Server()
{
    // delete m_dataBase;
    delete pool;
}

void Server::startServer(qint16 port)
{
    if(!this->listen(QHostAddress::Any, port))
    {
        ServerLogs->log("Faild to Initialzie server!!");
        qInfo() << this->errorString();
        return;
    }
    ServerLogs->log ("Listening on port: " + QString::number(port));
    qInfo() << ("Listening on port: " + QString::number(port));
}



void Server::quitServer()
{
    ServerLogs->log("Closing server...");
    delete pool;
    this->close();
}

void Server::incomingConnection(qintptr handle)
{
    qInfo() << QThread::currentThread();
    Client *handler = new Client(handle); //creating  a new connection in another thread.
    handler->setAutoDelete(true);
    pool->start(handler);//starting a thread for the new connected client.
}

