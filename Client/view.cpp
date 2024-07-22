#include "view.h"

View::View(QWidget *parent)
    : QWidget{parent}
{
    m_mainWindow = new MainWindow(this);

    m_control = new Control(this);
    connect(this, &View::makeRequest, m_control, &Control::makeRequest);
    connect(this, &View::RC_View_Control_Signal, m_control, &Control::RC_View_Control_Slot);

    connect(m_control, &Control::SH_Contor_View_connected_signal, this, &View::SH_Contor_View_connected_slot);
    connect(m_control, &Control::SH_Contor_View_disconnected_signal, this, &View::SH_Contor_View_disconnected_slot);

    connect(m_control, &Control::adminScreen_signal, this, &View::adminScreen_slot); // to view admin screen.
    connect(m_control, &Control::UserScreen_signal, this, &View::UserScreen_slot);   // to view admin screen.

    connect(m_control, &Control::CU_Control_Client, this, &View::CU_Client_View);
    connect(m_control, &Control::UU_Control_Client, this, &View::UU_Client_View);

    connect(m_control, &Control::DU_Control_Client, this, &View::DU_Client_View);

    connect(m_control, &Control::AN_Control_View_action, this, &View::AN_Control_View_action);
    connect(m_control, &Control::AB_Control_View_action, this, &View::AB_Control_View_action);
    connect(m_control, &Control::DB_Control_View_action, this, &View::DB_Control_View_action);

    connect(m_control, &Control::MT_Control_View_action, this, &View::MT_Control_View_action);
    connect(m_control, &Control::TA_Control_View_action, this, &View::TA_Control_View_action);

    connect(m_control, &Control::TH_Control_View_action, this, &View::TH_Control_View_action);


    //error connections

    connect(m_control, &Control::existUsr_Control_View_action, this, &View::existUsr_Control_View_action);
    connect(m_control, &Control::InvalidTransaction_Control_View_action, this, &View::InvalidTransaction_Control_View_action);
    connect(m_control, &Control::wrongUsr_Control_View_action, this, &View::wrongUsr_Control_View_action);
    connect(m_control, &Control::noUsr_Control_View_action, this, &View::noUsr_Control_View_action);
    connect(m_control, &Control::ServerError_Control_View_action, this, &View::ServerError_Control_View_action);

    connect(m_control, &Control::closedSocket_Control_View_signal, this, &View::closedSocket_Control_View_slot);


    connect(m_mainWindow, &MainWindow::sendRequest_mW_View, this, &View::sendRequest_mW_View);
    connect(m_mainWindow, &MainWindow::RC_MW_View_signal, this, &View::RC_MW_View_slot);


    m_mainWindow->show();

    m_adminWindow = nullptr;
    m_userWindow = nullptr;
}

void View::mainWindow_View()
{
    qInfo() << "mainWindow reached";
    m_mainWindow = new MainWindow(this);
    connect(m_mainWindow, &MainWindow::sendRequest_mW_View, this, &View::sendRequest_mW_View);
    connect(m_mainWindow, &MainWindow::RC_MW_View_signal, this, &View::RC_MW_View_slot);
    m_mainWindow->disable_refresh();

    if(m_adminWindow != nullptr)
    {
        m_mainWindow->show();

        delete m_adminWindow;
        m_adminWindow = nullptr;
    }
    else
    {
        m_mainWindow->show();
        delete m_userWindow;
        m_userWindow = nullptr;
    }
}


void View::sendRequest_mW_View(QByteArray request)
{
    qInfo() << "signal emitted from mainWindow to View Successfully!";
    emit makeRequest(request);
}

void View::adminScreen_slot()
{
    qInfo() << "admin screen Initialize!";

    delete m_mainWindow;
    m_mainWindow = nullptr;
    m_adminWindow = new AdminDialog(this);//temp
    connect(m_adminWindow, &AdminDialog::CU_Admin_View_Signal, this, &View::CU_Admin_View_Slot);
    connect(m_adminWindow, &AdminDialog::AN_Admin_View_Signal, this, &View::AN_Admin_View_Slot);
    connect(m_adminWindow, &AdminDialog::AB_Admin_View_Signal, this, &View::AB_Admin_View_Slot);
    connect(m_adminWindow, &AdminDialog::DU_Admin_View_Signal, this, &View::DU_Admin_View_Slot);
    connect(m_adminWindow, &AdminDialog::UU_Admin_View_Signal, this, &View::UU_Admin_View_Slot);
    connect(m_adminWindow, &AdminDialog::DB_Admin_View_Signal, this, &View::DB_Admin_View_Slot);
    connect(m_adminWindow, &AdminDialog::TH_Admin_View_Signal, this, &View::TH_Admin_View_Slot);

    connect(m_adminWindow, &AdminDialog::mainWindow_View, this, &View::mainWindow_View);



    m_adminWindow->show();
}

void View::UserScreen_slot()
{
    qInfo() << "I'm in UserScreen_slot in view class";
    delete m_mainWindow;
    m_mainWindow = nullptr;

    m_userWindow = new UserDialog(this);


    connect(m_userWindow, &UserDialog::mainWindow_View, this, &View::mainWindow_View);

    connect(m_userWindow, &UserDialog::MT_User_View_Signal, this, &View::MT_User_View_Slot);
    connect(m_userWindow, &UserDialog::TA_User_View_Signal, this, &View::TA_User_View_Slot);
    connect(m_userWindow, &UserDialog::TH_User_View_Signal, this, &View::TH_User_View_Slot);
    connect(m_userWindow, &UserDialog::AN_User_View_Signal, this, &View::AN_User_View_Slot);
    connect(m_userWindow, &UserDialog::AB_User_View_Signal, this, &View::AB_User_View_Slot);

    m_userWindow->show();
}



void View::CU_Admin_View_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from AdminDialog to View successfully!";
    emit makeRequest(_request);
}

void View::UU_Admin_View_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from AdminDialog to View successfully!";
    emit makeRequest(_request);
}

void View::CU_Client_View()
{
    qInfo() << "Control and View wrapped successfully";
    m_adminWindow->m_createUsr->CreateUsr_OK();
    m_adminWindow->show();//temp
}

void View::UU_Client_View()
{
    qInfo() << "Control and View wrapped successfully";
    m_adminWindow->upUsr->UpdateUsr_OK();
    m_adminWindow->show();//temp
}

void View::DU_Client_View(QJsonObject r_obj)
{
    qInfo() << "Performing action on after deleting user.";
    m_adminWindow->delUser->DeleteUsr_OK(r_obj);
}

void View::AN_Admin_View_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from admin class to view class successfully!";
    //emitting signal to Client class.
    emit makeRequest(_request);
}

void View::AB_Admin_View_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from admin class to view class successfully!";
    //emitting signal to Client class.
    emit makeRequest(_request);
}

void View::DU_Admin_View_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from admin class to view class successfully!";
    //emitting signal to Client class.
    emit makeRequest(_request);
}

void View::DB_Admin_View_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from admin class to view class successfully!";
    //emitting signal to Client class.
    emit makeRequest(_request);
}

void View::TH_Admin_View_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from admin class to view class successfully!";
    //emitting signal to Client class.
    emit makeRequest(_request);
}

void View::TH_User_View_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from admin class to view class successfully!";
    //emitting signal to Client class.
    emit makeRequest(_request);
}

void View::AN_User_View_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from admin class to view class successfully!";
    //emitting signal to Client class.
    emit makeRequest(_request);
}

void View::AB_User_View_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from admin class to view class successfully!";
    //emitting signal to Client class.
    emit makeRequest(_request);
}


void View::AN_Control_View_action(QJsonObject r_obj)
{
    qInfo() << "Signal emitted from control to view successfully";
    if(m_adminWindow != nullptr)
    {
        m_adminWindow->accNum->accountNum_OK(r_obj);
    }
    else if(m_userWindow != nullptr)
    {
        m_userWindow->accNum->accountNum_OK(r_obj);
    }
}

void View::AB_Control_View_action(QJsonObject r_obj)
{
    qInfo() << "Signal emitted from control to view successfully";
    if(m_adminWindow != nullptr)
    {
        m_adminWindow->accBalance->accountBalance_OK(r_obj);
    }
    else if(m_userWindow != nullptr)
    {
        m_userWindow->accBalance->accountBalance_OK(r_obj);
    }
}

void View::DB_Control_View_action(QJsonObject r_obj)
{
    qInfo() << "Signal emitted from control to view successfully";
    m_adminWindow->dbView->dbView_OK(r_obj);
}

void View::MT_Control_View_action(QJsonObject r_obj)
{
    qInfo() << "I'm here in view class mk";
    m_userWindow->mkTrans->makeTransaction_Action(r_obj);
}

void View::TH_Control_View_action(QJsonObject r_obj)
{
    qInfo() << "final stage";
    if(m_adminWindow !=nullptr)
    {
        m_adminWindow->trHistory->TransactionHistory_action(r_obj);
    }
    else if(m_userWindow !=nullptr)
    {
        m_userWindow->trHistory->TransactionHistory_action(r_obj);
    }
}

void View::TA_Control_View_action()
{
    qInfo() << "I'm here in view class mk";
    m_userWindow->trAmount->TransferAmount_Action();
}


//error actions
void View::existUsr_Control_View_action()
{
    qInfo() << "final stage";
    if(m_adminWindow !=nullptr)
    {
        if(m_adminWindow->m_createUsr != nullptr)
        {
            m_adminWindow->m_createUsr->existUsr_error();
        }
        else if(m_adminWindow->upUsr != nullptr)
        {
            m_adminWindow->upUsr->existUsr_error();
        }
    }
}

void View::InvalidTransaction_Control_View_action()
{
    qInfo() << "final stage";

    if(m_userWindow !=nullptr)
    {
        if(m_userWindow->mkTrans != nullptr)
        {
            m_userWindow->mkTrans->InvalidTransaction_error();
        }
        else if(m_userWindow->trAmount != nullptr)
        {
            m_userWindow->trAmount->InvalidTransaction_error();
        }
    }
}

void View::wrongUsr_Control_View_action()
{
    qInfo() << "final stage";

    if(m_mainWindow != nullptr)
    {
        m_mainWindow->wrongUsr_error();
    }
}

void View::noUsr_Control_View_action()
{
    qInfo() << "final stage";
    if(m_adminWindow !=nullptr)
    {
        if(m_adminWindow->accNum != nullptr)
        {
            m_adminWindow->accNum->noUsr_error();
        }
        else if(m_adminWindow->accBalance != nullptr)
        {
            m_adminWindow->accBalance->noUsr_error();
        }
        else if(m_adminWindow->delUser != nullptr)
        {
            m_adminWindow->delUser->noUsr_error();
        }
        else if(m_adminWindow->upUsr != nullptr)
        {
            m_adminWindow->upUsr->noUsr_error();
        }
        else if(m_adminWindow->trHistory != nullptr)
        {
            m_adminWindow->trHistory->noUsr_error();
        }

    }
    else if(m_userWindow !=nullptr)
    {
        if(m_userWindow->accNum != nullptr)
        {
            m_userWindow->accNum->noUsr_error();
        }
        else if(m_userWindow->accBalance != nullptr)
        {
            m_userWindow->accBalance->noUsr_error();
        }
        else if(m_userWindow->trHistory != nullptr)
        {
            m_userWindow->trHistory->noUsr_error();
        }
        else if(m_userWindow->mkTrans != nullptr)
        {
            m_userWindow->mkTrans->noUsr_error();
        }
        else if(m_userWindow->trAmount != nullptr)
        {
            m_userWindow->trAmount->noUsr_error();
        }
    }
    if(m_mainWindow != nullptr)
    {
        m_mainWindow->noUsr_error();
    }
}

void View::ServerError_Control_View_action()
{
    qInfo() << "final stage";
    if(m_adminWindow !=nullptr)
    {
        if(m_adminWindow->m_createUsr != nullptr)
        {
            m_adminWindow->m_createUsr->ServerError_error();
        }
        else if(m_adminWindow->accNum != nullptr)
        {
            m_adminWindow->accNum->ServerError_error();
        }
        else if(m_adminWindow->accBalance != nullptr)
        {
            m_adminWindow->accBalance->ServerError_error();
        }
        else if(m_adminWindow->delUser != nullptr)
        {
            m_adminWindow->delUser->ServerError_error();
        }
        else if(m_adminWindow->upUsr != nullptr)
        {
            m_adminWindow->upUsr->ServerError_error();
        }
        else if(m_adminWindow->dbView != nullptr)
        {
            m_adminWindow->dbView->ServerError_error();
        }
        else if(m_adminWindow->trHistory != nullptr)
        {
            m_adminWindow->trHistory->ServerError_error();
        }
    }
    else if(m_userWindow !=nullptr)
    {
        if(m_userWindow->accNum != nullptr)
        {
            m_userWindow->accNum->ServerError_error();
        }
        else if(m_userWindow->accBalance != nullptr)
        {
            m_userWindow->accBalance->ServerError_error();
        }
        else if(m_userWindow->trHistory != nullptr)
        {
            m_userWindow->trHistory->ServerError_error();
        }
        else if(m_userWindow->mkTrans != nullptr)
        {
            m_userWindow->mkTrans->ServerError_error();
        }
        else if(m_userWindow->trAmount != nullptr)
        {
            m_userWindow->trAmount->ServerError_error();
        }
    }
}

void View::RC_MW_View_slot(QString hostIP)
{
    qInfo() << "I reached View from MW to reconnect";
    emit RC_View_Control_Signal(hostIP);
}

void View::SH_Contor_View_connected_slot()
{
    qInfo() << "I'll disable refresh button";
    QMessageBox::information(this, "Information", "Connected to Bank server successfully!");//temp
    m_mainWindow->disable_refresh();
    m_mainWindow->enable_login();
}

void View::SH_Contor_View_disconnected_slot()
{
    qInfo() << "I'll return you  home and enable refresh";
    QMessageBox::critical(this, "Critical", "You're Offline");

    //temp
    if(m_mainWindow != nullptr)
    {
        m_mainWindow->enable_refresh();
    }

    else if(m_adminWindow != nullptr)
    {
        m_mainWindow = new MainWindow(this);
        connect(m_mainWindow, &MainWindow::sendRequest_mW_View, this, &View::sendRequest_mW_View);
        connect(m_mainWindow, &MainWindow::RC_MW_View_signal, this, &View::RC_MW_View_slot);



        m_mainWindow->enable_refresh();
        delete m_adminWindow;
        m_adminWindow = nullptr;
        m_mainWindow->show();
    }
    else if(m_userWindow != nullptr)
    {
        m_mainWindow = new MainWindow(this);
        connect(m_mainWindow, &MainWindow::sendRequest_mW_View, this, &View::sendRequest_mW_View);
        connect(m_mainWindow, &MainWindow::RC_MW_View_signal, this, &View::RC_MW_View_slot);



        m_mainWindow->enable_refresh();
        delete m_userWindow;
        m_userWindow = nullptr;
        m_mainWindow->show();
    }
}

void View::closedSocket_Control_View_slot()
{
    m_mainWindow->closedSocket_MessageBox();
}



void View::MT_User_View_Slot(QByteArray l_request)
{
    qInfo() << "Signal emitted from User to view successfully";
    emit makeRequest(l_request);
}

void View::TA_User_View_Slot(QByteArray l_request)
{
    qInfo() << "Signal emitted from User to view successfully";
    emit makeRequest(l_request);
}


