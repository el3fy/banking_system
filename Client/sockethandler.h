#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <QObject>
#include <QMetaEnum>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

class socketHandler : public QObject
{
    Q_OBJECT
public:
    explicit socketHandler(QString hostName, qint16 port, QObject *parent);
    ~socketHandler();
    void write_toSocket(QByteArray);
    void re_connect();
    void disconnect();

    QString hostName() const;
    void setHostName(const QString &newHostName);

private slots:
    void connected();
    void disconnected();
    void errorOccurred(QAbstractSocket::SocketError socketError);
    void hostFound();
    void stateChanged(QAbstractSocket::SocketState socketState);
    void readyRead();


signals:
    void adminScreen_Init(); //emitted from socketHandler to Control
    void UserScreen_Init(); //emitted from socketHandler to Control

    void CU_SH_Control_Signal();
    void UU_SH_Control_Signal();
    void DU_SH_Control_Signal(QJsonObject);
    void AN_SockectHandler_Control_Signal(QJsonObject);
    void AB_SockectHandler_Control_Signal(QJsonObject);
    void DB_SockectHandler_Control_Signal(QJsonObject);
    void TH_SockectHandler_Control_Signal(QJsonObject);

    void MT_ScoketHandler_Control_Signal(QJsonObject);
    void TA_ScoketHandler_Control_Signal();

    //error signals
    //existUsr = -5, InvalidTransaction_ID , wrongUsr, noUsr, ServerError_ID

    void existUsr_Control_signal();
    void InvalidTransaction_Control_signal();
    void wrongUsr_Control_signal();
    void noUsr_Control_signal();
    void ServerError_Control_signal();
    void noConnection_Control_signal();

    void closedSocket_Signal();

    void SH_Control_connected_Signal(); // at start of booting
    void SH_Control_disconnected_signal();
private:
    QTcpSocket *m_socket;
    QString m_hostName;
    qint16 m_port;
    enum actionList{existUsr = -5, InvalidTransaction_ID , wrongUsr, noUsr, ServerError_ID, userScreen, getAccount_Number, getAccount_Balance, TransHistory_ID, MakeTransaction_ID, TransferAmount_ID, ViewDatabase_ID, CreateUsr_ID, DelUser_ID, UpdateUser_ID}; // enum to switch when response comes.

};

#endif // SOCKETHANDLER_H
