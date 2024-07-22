#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include "accountnumber.h"
#include "accountbalance.h"
#include "maketransaction.h"
#include "transferamount.h"
#include "transhistory.h"

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = nullptr);
    ~UserDialog();
    AccountNumber *accNum;
    AccountBalance *accBalance;
    makeTransaction *mkTrans;
    TransferAmount *trAmount;
    TransHistory *trHistory;

signals:
    void mainWindow_View();
    void MT_User_View_Signal(QByteArray);
    void TA_User_View_Signal(QByteArray);
    void TH_User_View_Signal(QByteArray);
    void AN_User_View_Signal(QByteArray);
    void AB_User_View_Signal(QByteArray);

private slots:


    void MT_User_Slots(QByteArray);

    void TA_User_Slots(QByteArray);
    void TH_General_User_Slot(QByteArray);
    void AN_General_User_Slot(QByteArray);
    void AB_General_User_Slot(QByteArray);


    void on_returnHome_btn_2_clicked();

    void on_getAccoutn_btn_2_clicked();


    void on_makeTransaction_btn_clicked();

    void on_transferAmount_btn_clicked();

    void on_getBalance_btn_2_clicked();

    void on_transHistory_btn_2_clicked();

private:
    Ui::UserDialog *ui;
};

#endif // USERDIALOG_H
