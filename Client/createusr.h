#ifndef CREATEUSR_H
#define CREATEUSR_H

#include <QDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QJsonObject>
#include <QJsonDocument>

namespace Ui {
class CreateUsr;
}

class CreateUsr : public QDialog
{
    Q_OBJECT

public:
    explicit CreateUsr(QWidget *parent = nullptr);
    void CreateUsr_OK();
    //error actions
    void ServerError_error();
    void existUsr_error();

    ~CreateUsr();

signals:
    void CU_Admin_Signal(QByteArray);



private slots:
    void on_createUsr_btn_clicked();
    void checkInput();
    void on_pushButton_clicked();

private:
    Ui::CreateUsr *ui;

};

#endif // CREATEUSR_H
