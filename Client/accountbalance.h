#ifndef ACCOUNTBALANCE_H
#define ACCOUNTBALANCE_H

#include <QDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

namespace Ui {
class AccountBalance;
}

class AccountBalance : public QDialog
{
    Q_OBJECT

public:
    explicit AccountBalance(QWidget *parent = nullptr);
    void accountBalance_OK(QJsonObject);

    //error actions
    void ServerError_error();
    void noUsr_error();
    ~AccountBalance();

signals:
    void AB_General_Signal(QByteArray);
private slots:

    void on_close_btn_clicked();

    void on_Search_btn_clicked();

    void on_numBox_textChanged(const QString &arg1);


private:
    Ui::AccountBalance *ui;
    QRegularExpression numRegx;
};

#endif // ACCOUNTBALANCE_H
