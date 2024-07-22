#ifndef ACCOUNTNUMBER_H
#define ACCOUNTNUMBER_H

#include <QDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

namespace Ui {
class AccountNumber;
}

class AccountNumber : public QDialog
{
    Q_OBJECT

public:
    explicit AccountNumber(QWidget *parent = nullptr);
    void accountNum_OK(QJsonObject);

    //error actions
    void ServerError_error();
    void noUsr_error();

    ~AccountNumber();

private slots:


    void on_srch_btn_clicked();

    void on_back_btn_clicked();

    void on_nameBox_textChanged(const QString &arg1);

signals:
    // void AN_Admin_Signal(QByteArray);
    // void AN_User_Signal(QByteArray);
    void AN_General_Signal(QByteArray);

private:
    Ui::AccountNumber *ui;
    QRegularExpression usernameRegex;
};

#endif // ACCOUNTNUMBER_H
