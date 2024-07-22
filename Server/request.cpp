#include "request.h"

Request::Request()
    :dataBaseManager{Database::getInstance()}
{
   // dataBaseManager = dataBaseManager.getInstance();
    qInfo()<<"db request"<<&dataBaseManager;
    requestLogs = new Logger("./requsetLogs.log");
}

QByteArray Request::handleReaquest(QByteArray request)
{
    QJsonDocument doc = QJsonDocument::fromJson(request); //converting the request to QJsonDocument then to QJsonObject.

    QJsonObject requestObj = doc.object();

    QByteArray response;
    QJsonObject DB_response;

    int val = requestObj.value("RequestID").toString().toInt(); // obtaining the request ID to switch on it.
    qInfo() << "The value of Val: " << val;
    switch(val)
    {
    case LogIn_ID:
       DB_response = dataBaseManager.logIn(requestObj); //login ID
        qInfo() << "Login reached";
        break;
    case GetAccuont_ID:
        DB_response = dataBaseManager.getAccount_Number(requestObj); // account number ID
        break;
    case ViewAccount_ID:
        DB_response = dataBaseManager.viewAccount_Balance(requestObj); // account Balance ID
        break;
    case ViewTransactionHistory_ID:
        DB_response = dataBaseManager.viewTransaction_History(requestObj); // transaction History ID
        break;
    case MakeTransaction_ID:
        DB_response = dataBaseManager.makeTransaction(requestObj); // make transaction ID
        break;
    case TransferAmount_ID:
        DB_response = dataBaseManager.transferAmount(requestObj); // transfer amount ID
        break;
    case ViewBankDB_ID:
        DB_response = dataBaseManager.viewBankDB(requestObj); // Bank database ID
        break;
    case CreateUser_ID:
        DB_response = dataBaseManager.createUser(requestObj); // create user ID
         qInfo() << "create user reached";
         qInfo() << DB_response["ResponseID"].toString().toInt();
        break;
    case DeleteUser_ID:
        DB_response = dataBaseManager.deleteUser(requestObj); // delete user ID
        break;
    case UpDateUser_ID:
        DB_response = dataBaseManager.updateUser(requestObj); // update user ID
        break;
    default:
        response.append(1);
    }
    QJsonDocument docResponse(DB_response); // receving Database response and converting it to QJsonDocument then tho QByteArray and resend it to request handler.
    response = docResponse.toJson();
    return response;
}
