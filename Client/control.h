#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include "sockethandler.h"
class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = nullptr);
    ~Control();

public slots:
    void makeRequest(QByteArray);
    void adminScreen_Init(); // from socketHandler to Control
    void UserScreen_Init(); // from socketHandler to Control

    void CU_SH_Control_Slot();
    void UU_SH_Control_Slot();
    void DU_SH_Control_Slot(QJsonObject);
    void AN_SockectHandler_Control_Slot(QJsonObject);
    void AB_SockectHandler_Control_Slot(QJsonObject);
    void DB_SockectHandler_Control_Slot(QJsonObject);
    void TH_SockectHandler_Control_Slot(QJsonObject);


    void MT_ScoketHandler_Control_Slot(QJsonObject);
    void TA_ScoketHandler_Control_Slot();

    //error slots

    void existUsr_Control_slot();
    void InvalidTransaction_Control_slot();
    void wrongUsr_Control_slot();
    void noUsr_Control_slot();
    void ServerError_Control_slot();
    // void noConnection_Control_slot();

    void closedSocket_Slot();

    //reconnect slot
    void RC_View_Control_Slot(QString hostIP);
    void SH_Control_connected_Slot(); //at start of connected state.
    void SH_Control_disconnected_slot();

signals:
    void adminScreen_signal(); //signal to be connected to slot in view
    void UserScreen_signal();  //signal to be connected to slot in view

    void CU_Control_Client();
    void UU_Control_Client();
    void DU_Control_Client(QJsonObject);
    void AN_Control_View_action(QJsonObject);
    void AB_Control_View_action(QJsonObject);
    void DB_Control_View_action(QJsonObject);
    void TH_Control_View_action(QJsonObject);

    void MT_Control_View_action(QJsonObject);
    void TA_Control_View_action();

    //error actions
    void existUsr_Control_View_action();
    void InvalidTransaction_Control_View_action();
    void wrongUsr_Control_View_action();
    void noUsr_Control_View_action();
    void ServerError_Control_View_action();
    void noConnection_Control_View_action();

    void SH_Contor_View_connected_signal();
    void SH_Contor_View_disconnected_signal();

    void closedSocket_Control_View_signal();

public:
    socketHandler *m_handler;
};

#endif // CONTROL_H
