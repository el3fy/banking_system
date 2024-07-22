#include "control.h"

Control::Control(QObject *parent)
    : QObject{parent}
{

    m_handler = new socketHandler("127.0.0.1",2222, this);

    connect(m_handler, &socketHandler::SH_Control_connected_Signal, this, &Control::SH_Control_connected_Slot);
    connect(m_handler, &socketHandler::SH_Control_disconnected_signal, this, &Control::SH_Control_disconnected_slot);

    connect(m_handler, &socketHandler::adminScreen_Init, this, &Control::adminScreen_Init);
    connect(m_handler, &socketHandler::UserScreen_Init, this, &Control::UserScreen_Init);

    connect(m_handler, &socketHandler::CU_SH_Control_Signal, this, &Control::CU_SH_Control_Slot);
    connect(m_handler, &socketHandler::DU_SH_Control_Signal, this, &Control::DU_SH_Control_Slot);
    connect(m_handler, &socketHandler::UU_SH_Control_Signal, this, &Control::UU_SH_Control_Slot);

    connect(m_handler, &socketHandler::AN_SockectHandler_Control_Signal, this, &Control::AN_SockectHandler_Control_Slot);
    connect(m_handler, &socketHandler::AB_SockectHandler_Control_Signal, this, &Control::AB_SockectHandler_Control_Slot);
    connect(m_handler, &socketHandler::DB_SockectHandler_Control_Signal, this, &Control::DB_SockectHandler_Control_Slot);
    connect(m_handler, &socketHandler::TH_SockectHandler_Control_Signal, this, &Control::TH_SockectHandler_Control_Slot);


    connect(m_handler, &socketHandler::MT_ScoketHandler_Control_Signal, this, &Control::MT_ScoketHandler_Control_Slot);
    connect(m_handler, &socketHandler::TA_ScoketHandler_Control_Signal, this, &Control::TA_ScoketHandler_Control_Slot);

    connect(m_handler, &socketHandler::existUsr_Control_signal, this, &Control::existUsr_Control_slot);
    connect(m_handler, &socketHandler::InvalidTransaction_Control_signal, this, &Control::InvalidTransaction_Control_slot);
    connect(m_handler, &socketHandler::wrongUsr_Control_signal, this, &Control::wrongUsr_Control_slot);
    connect(m_handler, &socketHandler::noUsr_Control_signal, this, &Control::noUsr_Control_slot);
    connect(m_handler, &socketHandler::ServerError_Control_signal, this, &Control::ServerError_Control_slot);

    connect(m_handler, &socketHandler::closedSocket_Signal, this, &Control::closedSocket_Slot);

}

Control::~Control()
{
    m_handler->disconnect();
    delete m_handler;
    m_handler = nullptr;
    qInfo() << "socket deleted successfully by Control in addtion to control itself";
}

void Control::makeRequest(QByteArray _request)
{

    qInfo() << "Request recieved to socketHandler successfully.";
    m_handler->write_toSocket(_request);
}

void Control::adminScreen_Init()
{
    qInfo() << "Control emits signal";
    emit adminScreen_signal();
}

void Control::UserScreen_Init()
{
    qInfo() << "Control emits signal UserScreen_signal();";
    emit UserScreen_signal();
}



void Control::CU_SH_Control_Slot()
{
    qInfo() << "socketHandler signal emitted to Control successfully";
    emit CU_Control_Client();
}

void Control::UU_SH_Control_Slot()
{
    qInfo() << "socketHandler signal emitted to Control successfully";
    emit UU_Control_Client();
}

void Control::DU_SH_Control_Slot(QJsonObject r_obj)
{
    qInfo() << "socketHandler signal emitted to Control successfully";
    emit DU_Control_Client(r_obj);
}

void Control::AN_SockectHandler_Control_Slot(QJsonObject r_obj)
{
    qInfo() << "Signal emitted from socketHandler class to Controls Class successfully!";
    emit AN_Control_View_action(r_obj);
}

void Control::AB_SockectHandler_Control_Slot(QJsonObject r_obj)
{
    qInfo() << "Signal emitted from socketHandler class to Controls Class successfully!";
    emit AB_Control_View_action(r_obj);
}

void Control::DB_SockectHandler_Control_Slot(QJsonObject r_obj)
{
    qInfo() << "Signal emitted from socketHandler class to Controls Class successfully!";
    emit DB_Control_View_action(r_obj);
}

void Control::TH_SockectHandler_Control_Slot(QJsonObject r_obj)
{
    qInfo() << "Signal emitted from socketHandler class to Controls Class successfully!";
    emit TH_Control_View_action(r_obj);
}

void Control::MT_ScoketHandler_Control_Slot(QJsonObject r_obj)
{
    emit MT_Control_View_action(r_obj);
}

void Control::TA_ScoketHandler_Control_Slot()
{
    emit TA_Control_View_action();
}

// void existUsr_Control_View_action();
// void InvalidTransaction_Control_View_action();
// void wrongUsr_Control_View_action();
// void noUsr_Control_View_action();
// void ServerError_Control_View_action();
// void noConnection_Control_View_action();

void Control::existUsr_Control_slot()
{
    qInfo() << "existUsr error to view";
    emit existUsr_Control_View_action();
}

void Control::InvalidTransaction_Control_slot()
{
    qInfo() << "InvalidTransaction error to view";
    emit InvalidTransaction_Control_View_action();
}

void Control::wrongUsr_Control_slot()
{
    qInfo() << "wrongUsr error to view";
    emit wrongUsr_Control_View_action();
}

void Control::noUsr_Control_slot()
{
    qInfo() << "noUsr error to view";
    emit noUsr_Control_View_action();
}

void Control::ServerError_Control_slot()
{
    qInfo() << "ServerError error to view";
    emit ServerError_Control_View_action();
}

void Control::closedSocket_Slot()
{
    emit closedSocket_Control_View_signal();
}

void Control::RC_View_Control_Slot(QString hostIP)
{
    qInfo() << "I reached re_connect button";
    m_handler->setHostName(hostIP);
    m_handler->re_connect();
}

void Control::SH_Control_connected_Slot()
{
    emit SH_Contor_View_connected_signal();
}

void Control::SH_Control_disconnected_slot()
{
    emit SH_Contor_View_disconnected_signal();
}




