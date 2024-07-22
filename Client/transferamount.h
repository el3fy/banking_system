#ifndef TRANSFERAMOUNT_H
#define TRANSFERAMOUNT_H

#include <QDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class TransferAmount;
}

class TransferAmount : public QDialog
{
    Q_OBJECT

public:
    explicit TransferAmount(QWidget *parent = nullptr);
    void TransferAmount_Action();

    //error actions
    void ServerError_error();
    void InvalidTransaction_error();
    void noUsr_error();

    ~TransferAmount();


signals:
    void TA_User_Signal(QByteArray);
private slots:
    void on_close_btn_clicked();

    void on_trans_btn_clicked();

    void on_numBox_1_textChanged(const QString &arg1);

    void on_numBox_2_textChanged(const QString &arg1);

    void on_amountBox_textChanged(const QString &arg1);

private:
    Ui::TransferAmount *ui;
    QRegularExpression num1_Regx;
    QRegularExpression num2_Regx;
    QRegularExpression amountRegx;
};

#endif // TRANSFERAMOUNT_H
