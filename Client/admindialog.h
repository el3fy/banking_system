#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "createusr.h"
#include "accountnumber.h"
#include "accountbalance.h"
#include "deleteuser.h"
#include "updateuser.h"
#include "databaseview.h"
#include "transhistory.h"

namespace Ui {
class AdminDialog;
}

class AdminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AdminDialog(QWidget *parent = nullptr);


    ~AdminDialog();
    CreateUsr *m_createUsr;
    AccountNumber *accNum;
    AccountBalance *accBalance;
    DeleteUser *delUser;
    UpdateUser *upUsr;
    TransHistory *trHistory;
    DatabaseView *dbView;


private slots:
    void on_createUsr_btn_clicked();
    void CU_Admin_Slot(QByteArray);
    // void AN_Admin_Slot(QByteArray);
    // void AB_Admin_Slot(QByteArray);

    void DU_Admin_Slot(QByteArray);
    void UU_Admin_Slot(QByteArray);
    void DB_Admin_Slot(QByteArray);
    void TH_General_Admin_Slot(QByteArray);
    void AN_General_Admin_Slot(QByteArray);
    void AB_General_Admin_Slot(QByteArray);

    void on_returnHome_btn_clicked();

    void on_getAccoutn_btn_clicked();

    void on_getBalance_btn_clicked();

    void on_deleteAccoutn_btn_clicked();

    void on_transHistory_btn_clicked();

    void on_updateUsr_btn_clicked();

    void on_viewDatabase_btn_clicked();

signals:
    void CU_Admin_View_Signal(QByteArray);
    void AN_Admin_View_Signal(QByteArray);
    void AB_Admin_View_Signal(QByteArray);
    void DU_Admin_View_Signal(QByteArray);
    void UU_Admin_View_Signal(QByteArray);
    void DB_Admin_View_Signal(QByteArray);
    void TH_Admin_View_Signal(QByteArray);
    void mainWindow_View();

private:
    Ui::AdminDialog *ui;

};

#endif // ADMINDIALOG_H
