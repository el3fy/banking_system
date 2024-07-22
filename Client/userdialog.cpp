#include "userdialog.h"
#include "ui_userdialog.h"

UserDialog::UserDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserDialog)
{
    ui->setupUi(this);
    accNum = nullptr;
    accBalance = nullptr;
    mkTrans = nullptr;
    trAmount = nullptr;
    trHistory = nullptr;
}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog::MT_User_Slots(QByteArray l_data)
{
    qInfo() << "Signal emitted from makeTranscation to user successfully";
    emit MT_User_View_Signal(l_data);
}

void UserDialog::TA_User_Slots(QByteArray l_data)
{
    qInfo() << "Signal emitted from transferAmount to user successfully";
    emit TA_User_View_Signal(l_data);
}

void UserDialog::TH_General_User_Slot(QByteArray l_data)
{
    qInfo() << "Signal emitted from TransactionHistory to user successfully";
    emit TH_User_View_Signal(l_data);
}

void UserDialog::AN_General_User_Slot(QByteArray l_data)
{
    qInfo() << "Signal emitted from get account number to user successfully";
    emit AN_User_View_Signal(l_data);
}

void UserDialog::AB_General_User_Slot(QByteArray l_data)
{
    qInfo() << "Signal emitted from get account balance to user successfully";
    emit AB_User_View_Signal(l_data);
}





void UserDialog::on_returnHome_btn_2_clicked()
{
    qInfo() << "return main window successfully!";
    emit mainWindow_View();
}


void UserDialog::on_getAccoutn_btn_2_clicked()
{
    //create a new instanse of accountNum
    accNum = new AccountNumber(this);
    //connect the signal of ok button to slot of admin
    connect(accNum, &AccountNumber::AN_General_Signal, this, &UserDialog::AN_General_User_Slot);
    //show the new widget
    accNum->exec();
}




void UserDialog::on_makeTransaction_btn_clicked()
{
    mkTrans = new makeTransaction(this);
    //connections
    connect(mkTrans, &makeTransaction::MT_User_Signal, this, &UserDialog::MT_User_Slots);
    //show
    mkTrans->exec();
}


void UserDialog::on_transferAmount_btn_clicked()
{
    trAmount = new TransferAmount(this);
    //connections
    connect(trAmount, &TransferAmount::TA_User_Signal, this, &UserDialog::TA_User_Slots);
    //show
    trAmount->exec();
}





void UserDialog::on_getBalance_btn_2_clicked()
{
    qInfo() << "get balance fun reached";
    accBalance = new AccountBalance(this);
    //connect the signal of ok button to slot of admin
    connect(accBalance, &AccountBalance::AB_General_Signal, this, &UserDialog::AB_General_User_Slot);
    //show the new widget
    accBalance->exec();
}


void UserDialog::on_transHistory_btn_2_clicked()
{

    trHistory = new TransHistory(this);
    // //connections
     connect(trHistory, &TransHistory::TH_General_Signal, this, &UserDialog::TH_General_User_Slot);
    // //show
    trHistory->exec();
}

