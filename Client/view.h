#ifndef VIEW_H
#define VIEW_H
#include <QWidget>
#include "mainwindow.h"
#include "admindialog.h"
#include "userdialog.h"
#include "control.h"

class View : public QWidget
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
signals:

    void makeRequest(QByteArray);
    void RC_View_Control_Signal(QString hostIP);//temp

    void shutDown_Client_signal(); //to  destroy all components.

public slots:

    void mainWindow_View();
    void sendRequest_mW_View(QByteArray);
    void adminScreen_slot(); //connected on client class
    void UserScreen_slot(); //connected on client class

    void CU_Admin_View_Slot(QByteArray);
    void UU_Admin_View_Slot(QByteArray);
    void CU_Client_View();
    void UU_Client_View();
    void DU_Client_View(QJsonObject);
    void AN_Admin_View_Slot(QByteArray);
    void AB_Admin_View_Slot(QByteArray);
    void DU_Admin_View_Slot(QByteArray);
    void DB_Admin_View_Slot(QByteArray);
    void TH_Admin_View_Slot(QByteArray);
    void TH_User_View_Slot(QByteArray);
    void AN_User_View_Slot(QByteArray);
    void AB_User_View_Slot(QByteArray);
    void MT_User_View_Slot(QByteArray);
    void TA_User_View_Slot(QByteArray);

    void AN_Control_View_action(QJsonObject);
    void AB_Control_View_action(QJsonObject);
    void DB_Control_View_action(QJsonObject);
    void MT_Control_View_action(QJsonObject);
    void TH_Control_View_action(QJsonObject);

    void TA_Control_View_action();

    //error slots
    void existUsr_Control_View_action();
    void InvalidTransaction_Control_View_action();
    void wrongUsr_Control_View_action();
    void noUsr_Control_View_action();
    void ServerError_Control_View_action();
    // void noConnection_Control_View_action();


    void RC_MW_View_slot(QString hostIP);//reconnection slot

    void SH_Contor_View_connected_slot();
    void SH_Contor_View_disconnected_slot();

    void closedSocket_Control_View_slot();



public:
    MainWindow *m_mainWindow;
    AdminDialog *m_adminWindow;
    UserDialog *m_userWindow;
    Control *m_control;
};

#endif // VIEW_H
