#include "client.h"

Client::Client(qintptr socketDescriptor, QObject *parent)
    : QObject{parent}, m_socketDescriptor{socketDescriptor}
{
    ClientLogs = new Logger("./ClientLogs.log");
    l_handler = new Request();
}

void Client::disconnected()
{
    ClientLogs->log("socket has disconnected..");
    qInfo() << QThread::currentThread();
    socket->deleteLater();
}

void Client::readyRead() //waiting a request from client...
{
    QByteArray c_request = socket->readAll();//receving the request and storing it QByteArray object.
    qInfo()<<QString::fromUtf8(c_request);

    QByteArray l_response = l_handler->handleReaquest(c_request);//sending the client request to request handler to resolve it.

    QJsonDocument l_doc = QJsonDocument::fromJson(l_response); // converting the response fron QByteArray to JsonDocument.
    QJsonObject l_obj = l_doc.object(); // converting the response to JsonObject.
    qInfo() << "ResponseID>>>>>>>: " << l_obj.value("ResponseID").toString().toInt();

    socket->write(l_response); // sending the response to client side.
    socket->waitForBytesWritten();

    qInfo() << QThread::currentThread();

}

void Client::run()
{
    socket = new QTcpSocket();//creating a socket for the new incoming connection.
    QEventLoop loop; // event loop, the client still listinging until a disconnect signal been emitted.
    if(!socket->setSocketDescriptor(m_socketDescriptor))
    {
        ClientLogs->log("Failed"); //have to be changed to log.
        qCritical() << socket->errorString();
        ClientLogs->log(socket->errorString());
        delete socket;
        return;
    }

    //we've the use Qt::DirectConnection when we connect signals and slots to ensure that slots will be invoked in the singling thread.
    connect(socket, &QTcpSocket::disconnected, &loop, &QEventLoop::quit, Qt::DirectConnection); //connecting disconnect signal with quit slot.
    connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected, Qt::DirectConnection);
    connect(socket, &QTcpSocket::readyRead, this, &Client::readyRead, Qt::DirectConnection);
    qInfo() << QThread::currentThread();

    loop.exec();
}
