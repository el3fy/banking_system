#ifndef UPDATEUSER_H
#define UPDATEUSER_H

#include <QDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

namespace Ui {
class UpdateUser;
}

class UpdateUser : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateUser(QWidget *parent = nullptr);
    void UpdateUsr_OK();

    //error actions
    void ServerError_error();
    void noUsr_error();
    void existUsr_error();

    ~UpdateUser();

signals:
    void UU_Admin_Signal(QByteArray);
private slots:
    void on_update_Btn_clicked();

    void on_Close_btn_clicked();

    void on_numBox_textChanged(const QString &arg1);

    void on_nameBox_textChanged(const QString &arg1);

    void on_FullBox_textChanged(const QString &arg1);

    void on_AgeBox_textChanged(const QString &arg1);

    void on_PassBox_textChanged(const QString &arg1);

private:
    Ui::UpdateUser *ui;
    QRegularExpression numRegx;
    QRegularExpression usrnameRegx;
    QRegularExpression fullNameRegx;
    QRegularExpression passwordRegx;
    QRegularExpression ageRegx;


};

#endif // UPDATEUSER_H
