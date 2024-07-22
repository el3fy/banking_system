#ifndef DELETEUSER_H
#define DELETEUSER_H

#include <QDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class DeleteUser;
}

class DeleteUser : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteUser(QWidget *parent = nullptr);
    void DeleteUsr_OK(QJsonObject);

    //error actions
    void ServerError_error();
    void noUsr_error();

    ~DeleteUser();

signals:
    void DU_Admin_Signal(QByteArray);

private slots:
    void on_Search_btn_clicked();

    void on_close_btn_clicked();

    void on_numBox_textChanged(const QString &arg1);

private:
    Ui::DeleteUser *ui;
    QRegularExpression numRegx;
};

#endif // DELETEUSER_H
