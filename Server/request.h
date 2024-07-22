#ifndef REQUEST_H
#define REQUEST_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonParseError>
#include "logger.h"
#include "database.h"

class Request
{
public:
    Request();
    QByteArray handleReaquest(QByteArray request);
    // Database databaseManger;

private:
    enum requestIDs{LogIn_ID, GetAccuont_ID, ViewAccount_ID, ViewTransactionHistory_ID, MakeTransaction_ID, TransferAmount_ID, ViewBankDB_ID, CreateUser_ID, DeleteUser_ID, UpDateUser_ID};
    Logger *requestLogs;
    Database& dataBaseManager;
};

#endif // REQUEST_H
