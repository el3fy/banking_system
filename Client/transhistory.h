#ifndef TRANSHISTORY_H
#define TRANSHISTORY_H

#include <QDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTableWidget>

namespace Ui {
class TransHistory;
}

class TransHistory : public QDialog
{
    Q_OBJECT

public:
    explicit TransHistory(QWidget *parent = nullptr);
    void TransactionHistory_action(QJsonObject);

    //error actions
    void ServerError_error();
    void noUsr_error();

    ~TransHistory();


signals:

    void TH_General_Signal(QByteArray);//temp

private slots:
    void on_close_btn_clicked();



    void on_numBox_textChanged(const QString &arg1);

    void on_countBox_textChanged(const QString &arg1);


    void on_view_btn_clicked();

private:
    Ui::TransHistory *ui;
    QRegularExpression numRegx;
    QRegularExpression countRegx;
};

#endif // TRANSHISTORY_H
