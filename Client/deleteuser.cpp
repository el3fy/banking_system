#include "deleteuser.h"
#include "ui_deleteuser.h"

DeleteUser::DeleteUser(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteUser)
{
    ui->setupUi(this);
    numRegx.setPattern("^\\d{1,5}$");
    ui->numBox->setValidator(new QRegularExpressionValidator(numRegx,this));
}

void DeleteUser::DeleteUsr_OK(QJsonObject r_obj)
{
    QString delName = r_obj.value("DeletedName").toString();
    QMessageBox::information(this, "Information", "User: " + delName + " has been deleted successfully");
    this->parentWidget()->show();
}

void DeleteUser::ServerError_error()
{
    QMessageBox::critical(this, "critical", "Error on server can't access database");
}

void DeleteUser::noUsr_error()
{
QMessageBox::critical(this, "Critical", "User  not found!");
}

DeleteUser::~DeleteUser()
{
    delete ui;
}

void DeleteUser::on_Search_btn_clicked()
{
    if(ui->numBox->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Account number can't be empty!");
    }
    else
    {
        QString usrNum = ui->numBox->text().trimmed();
        QJsonObject l_obj;
        l_obj.insert("AccountNumber",usrNum);
        l_obj.insert("RequestID","8");
        QJsonDocument l_doc(l_obj);
        QByteArray l_request = l_doc.toJson(QJsonDocument::JsonFormat::Indented);
        qInfo() << "Emitting signal from Delete user to admin.";
        emit DU_Admin_Signal(l_request);
    }
}


void DeleteUser::on_close_btn_clicked()
{
    this->parentWidget()->show();
    delete this;
}

void DeleteUser::on_numBox_textChanged(const QString &arg1)
{
    if(ui->numBox->hasAcceptableInput() && !(ui->numBox->text().isEmpty()))
    {
        ui->numBox->setStyleSheet("QLineEdit{ color: green;}");
        ui->numChk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");

    }
    else
    {
        ui->numBox->setStyleSheet("QLineEdit{ color: red;}");
        ui->numChk->setStyleSheet("QLabel{color: red;}");
        ui->numChk->setText("Account number must be at least 1 number and not greater than 5 numbers");
    }
}
