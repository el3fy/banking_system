#include "admindialog.h"
#include "ui_admindialog.h"

AdminDialog::AdminDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminDialog)
{
    ui->setupUi(this);

    qInfo() << "Admin launched!";
    m_createUsr = nullptr;
    accNum = nullptr;
    accBalance = nullptr;
    delUser = nullptr;
    upUsr = nullptr;
    dbView = nullptr;
    trHistory = nullptr;
}

AdminDialog::~AdminDialog()
{
    qInfo() << "Admin has destroyed successfully";
    delete ui;
}


void AdminDialog::on_createUsr_btn_clicked()
{
    m_createUsr = new CreateUsr(this);
    connect(m_createUsr, &CreateUsr::CU_Admin_Signal, this, &AdminDialog::CU_Admin_Slot);
    m_createUsr->exec();
    /*this->hide();*///temp
}

void AdminDialog::CU_Admin_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from CreateUsr to AdminDialog successfully!";
    emit CU_Admin_View_Signal(_request);
}

void AdminDialog::AB_General_Admin_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from Account number class to admin class successfully!";
    //emit signal to View class
    emit AB_Admin_View_Signal(_request);
}


void AdminDialog::DU_Admin_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from Delete user class to admin class successfully!";
    //emit signal to View class
    emit DU_Admin_View_Signal(_request);
}

void AdminDialog::UU_Admin_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from update user class to admin class successfully!";
    //emit signal to View class
    emit UU_Admin_View_Signal(_request);
}

void AdminDialog::DB_Admin_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from database view class to admin class successfully!";
    //emit signal to View class
    emit DB_Admin_View_Signal(_request);
}

void AdminDialog::AN_General_Admin_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from Account number class to admin class successfully!";
        //emit signal to View class
        emit AN_Admin_View_Signal(_request);
}

// void AdminDialog::TH_Admin_Slot(QByteArray _request)
// {
//     qInfo() << "Signal emitted from transHistory view class to admin class successfully!";
//     emit TH_Admin_View_Signal(_request);
// }

void AdminDialog::TH_General_Admin_Slot(QByteArray _request)
{
    qInfo() << "Signal emitted from transHistory view class to admin class successfully!";
    emit TH_Admin_View_Signal(_request);
}



void AdminDialog::on_returnHome_btn_clicked()
{
    qInfo() << "return main window successfully!";
    emit mainWindow_View();
    // delete this;
}


void AdminDialog::on_getAccoutn_btn_clicked()
{
    //create a new instanse of accountNum
    accNum = new AccountNumber(this);
    //connect the signal of ok button to slot of admin
    connect(accNum, &AccountNumber::AN_General_Signal, this, &AdminDialog::AN_General_Admin_Slot);
    //show the new widget
    accNum->exec();

}


void AdminDialog::on_getBalance_btn_clicked()
{
    qInfo() << "get balance fun reached";
    accBalance = new AccountBalance(this);
    //connect the signal of ok button to slot of admin
    connect(accBalance, &AccountBalance::AB_General_Signal, this, &AdminDialog::AB_General_Admin_Slot);
    //show the new widget
    accBalance->exec();
}


void AdminDialog::on_deleteAccoutn_btn_clicked()
{
    qInfo() << "Delete user function reached.";
    delUser = new DeleteUser(this);
    //connect the signal of delete button to slot of admin
    connect(delUser, &DeleteUser::DU_Admin_Signal, this, &AdminDialog::DU_Admin_Slot);
    //show the widget.
    delUser->exec();
}


void AdminDialog::on_transHistory_btn_clicked()
{
    qInfo() << "View TransHistory function reached.";
    trHistory = new TransHistory(this);

    // connect(trHistory, &TransHistory::TH_Admin_Signal, this, &AdminDialog::TH_Admin_Slot);

    connect(trHistory, &TransHistory::TH_General_Signal, this, &AdminDialog::TH_General_Admin_Slot);//temp


    //show
    trHistory->show();
}


void AdminDialog::on_updateUsr_btn_clicked()
{
    qInfo() << "update user function reached";
    upUsr = new UpdateUser(this);
    // connect this signal of update button to slot of admin
    connect(upUsr, &UpdateUser::UU_Admin_Signal, this, &AdminDialog::UU_Admin_Slot);
    //show the widget
    upUsr->exec();
}


void AdminDialog::on_viewDatabase_btn_clicked()
{
    qInfo() << "Database view function reached";
    dbView = new DatabaseView(this);
    //connect signals and slots
    connect(dbView, &DatabaseView::DB_Admin_Signal, this, &AdminDialog::DB_Admin_Slot);
    //show the widget
    dbView->exec();
}

