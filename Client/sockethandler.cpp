#include "sockethandler.h"

socketHandler::socketHandler(QString hostName, qint16 port, QObject *parent)
    :m_hostName{hostName}, m_port{port}, QObject{parent}
{
    m_socket = new QTcpSocket(this);

    QAbstractSocket::connect(m_socket, &QTcpSocket::connected, this, &socketHandler::connected);
    QAbstractSocket::connect(m_socket, &QTcpSocket::disconnected, this, &socketHandler::disconnected);
    QAbstractSocket::connect(m_socket, &QTcpSocket::errorOccurred, this, &socketHandler::errorOccurred);
    QAbstractSocket::connect(m_socket, &QTcpSocket::hostFound, this, &socketHandler::hostFound);
    QAbstractSocket::connect(m_socket, &QTcpSocket::stateChanged, this, &socketHandler::stateChanged);
    QAbstractSocket::connect(m_socket, &QTcpSocket::readyRead, this, &socketHandler::readyRead);
}

socketHandler::~socketHandler()
{
    m_socket->close();
    m_socket->deleteLater();
}

void socketHandler::write_toSocket(QByteArray _request)
{
    if(!(m_socket->isOpen()) || m_socket == nullptr)
    {
        qInfo() << "socket is closed can't send anything";
        emit closedSocket_Signal();
        return;
    }
    m_socket->write(_request);
    m_socket->waitForBytesWritten();
    qInfo() << "Request sent successfully!";
}

void socketHandler::re_connect()
{
    qInfo() << "Try to re_connect again";

    if(m_socket == nullptr)
    {
        m_socket = new QTcpSocket(this);
        QAbstractSocket::connect(m_socket, &QTcpSocket::connected, this, &socketHandler::connected);
        QAbstractSocket::connect(m_socket, &QTcpSocket::disconnected, this, &socketHandler::disconnected);
        QAbstractSocket::connect(m_socket, &QTcpSocket::errorOccurred, this, &socketHandler::errorOccurred);
        QAbstractSocket::connect(m_socket, &QTcpSocket::hostFound, this, &socketHandler::hostFound);
        QAbstractSocket::connect(m_socket, &QTcpSocket::stateChanged, this, &socketHandler::stateChanged);
        QAbstractSocket::connect(m_socket, &QTcpSocket::readyRead, this, &socketHandler::readyRead);
    }

    if((m_socket->isOpen()))
    {
        m_socket->close();
    }
    m_socket->connectToHost(m_hostName, m_port);
    qInfo() << "the hostIP is: " << this->hostName();
    m_socket->waitForConnected();
}

void socketHandler::disconnect()
{
    qInfo() << "Socket closed";
    m_socket->close();
    m_socket->waitForDisconnected();
    // m_socket = nullptr;
}



void socketHandler::connected()
{
    qInfo() << "Connected to: " << m_hostName << " at port: " << m_port << " successfully.";
    //disable reconnect button.
    // emit SH_Control_connected_Signal();
}

void socketHandler::disconnected()
{
    qInfo() << "Disconnected from: " << m_hostName;
    qInfo() << "Socket closed";
    m_socket->close();
    //return to main menu.
    //enable recoonect button.
    // emit SH_Control_disconnected_signal();
    if(m_socket != nullptr)
    {
        m_socket->deleteLater();

        m_socket = nullptr;
    }
}

void socketHandler::errorOccurred(QAbstractSocket::SocketError socketError)
{
    qInfo() << "Error: " << socketError << " " << m_socket->errorString();
}

void socketHandler::hostFound()
{
    qInfo() << "Host found!";
}

void socketHandler::stateChanged(QAbstractSocket::SocketState socketState)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qInfo() << "State:" << metaEnum.valueToKey(socketState);
    if(socketState == metaEnum.keyToValue("UnconnectedState"))
    {
        qInfo() << "signal emitted from state changed in socketHandler(disconnected)";
        emit SH_Control_disconnected_signal();

    }
    else if(socketState == metaEnum.keyToValue("ConnectedState"))
    {
        qInfo() << "signal emitted from state changed in socketHandler(connected)";
        emit SH_Control_connected_Signal();
    }
}

void socketHandler:: readyRead ()
{
    qInfo() << "I'm in readyRead()!";
    QByteArray l_response = m_socket->readAll(); //receiving the response from the bank server.
    QJsonDocument l_doc = QJsonDocument::fromJson(l_response);
    QJsonObject l_obj = l_doc.object(); // converting the response to json object.
    bool isAdmin = l_obj.value("IsAdmin").toBool();
    auto checkID = l_obj.value("ResponseID").toString().toInt();
    qInfo() << "checkID: " << checkID;
    switch(checkID)
    {
    case existUsr:
        qInfo() << "username is allready exist";
        emit existUsr_Control_signal();
        break;

    case InvalidTransaction_ID:
        qInfo() << "Invalid transaction";
        emit InvalidTransaction_Control_signal();
        break;

    case wrongUsr:
        qInfo() << "Wrong username or password.";
        emit wrongUsr_Control_signal();
        break;

    case noUsr:
        qInfo() << "user not found";
        emit noUsr_Control_signal();
        break;

    case ServerError_ID:
        qInfo() << "Server error!";
        emit ServerError_Control_signal();
        break;

    case userScreen:
        if(isAdmin)
        {
            qInfo() << "Hello admin!";
            qInfo() << "AdmingScreen is emitting signal from socketHandler to Control";
            emit adminScreen_Init();
        }
        else
        {
            qInfo() << "Hello user!";
            qInfo() << "UserScreen signal is emitting from socketHandler to Control";
            emit UserScreen_Init();
        }
        break;

    case getAccount_Number:
        qInfo() << "Searching in database...";
        emit AN_SockectHandler_Control_Signal(l_obj);
        break;

    case getAccount_Balance:
        qInfo() << "getting account Balance";
        emit AB_SockectHandler_Control_Signal(l_obj);
        break;

    case TransHistory_ID:
        qInfo() << "transaction history get successfully";
        emit TH_SockectHandler_Control_Signal(l_obj);
        break;

    case MakeTransaction_ID:
        qInfo() << "Make transaction done successfully";
        emit MT_ScoketHandler_Control_Signal(l_obj);
        break;

    case TransferAmount_ID:
        qInfo() << "Transfer done successfully";
        emit TA_ScoketHandler_Control_Signal();
        break;

    case ViewDatabase_ID:
        qInfo() << "Database received successfully";
        emit DB_SockectHandler_Control_Signal(l_obj);
        break;

    case CreateUsr_ID:
        qInfo() << "Server has created new user successfully!";
        emit CU_SH_Control_Signal();
        break;

    case DelUser_ID:
        qInfo() << "Searching to user to delete it.";
        emit DU_SH_Control_Signal(l_obj);
        break;

    case UpdateUser_ID:
        qInfo() << "User's data updated successfully";
        emit UU_SH_Control_Signal();
        break;

    default:
        qInfo() << "Undefined Issue.";
        break;
    }
}

QString socketHandler::hostName() const
{
    return m_hostName;
}

void socketHandler::setHostName(const QString &newHostName)
{
    m_hostName = newHostName;
}

