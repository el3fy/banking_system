#include <QCoreApplication>
#include "server.h"
#include "logger.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Server myServer;


    myServer.startServer(2222);

    return a.exec();
}

