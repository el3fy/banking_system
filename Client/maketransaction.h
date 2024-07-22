#ifndef MAKETRANSACTION_H
#define MAKETRANSACTION_H

#include <QDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class makeTransaction;
}

class makeTransaction : public QDialog
{
    Q_OBJECT

public:
    explicit makeTransaction(QWidget *parent = nullptr);
    void makeTransaction_Action(QJsonObject);
    //error actions
    void ServerError_error();
    void InvalidTransaction_error();
    void noUsr_error();

    ~makeTransaction();


signals:
    void MT_User_Signal(QByteArray);

private slots:


    void on_close_btn_clicked();

    void on_makeTrans_btn_clicked();

    void on_numBox_textChanged(const QString &arg1);

    void on_amountBox_textChanged(const QString &arg1);

private:
    Ui::makeTransaction *ui;
    QRegularExpression numRegx;
    QRegularExpression amountRegx;

};

#endif // MAKETRANSACTION_H
