#include "accountbalance.h"
#include "ui_accountbalance.h"

AccountBalance::AccountBalance(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccountBalance)
{
    ui->setupUi(this);
    numRegx.setPattern("^\\d{1,5}$");
    ui->numBox->setValidator(new QRegularExpressionValidator(numRegx,this));
}

void AccountBalance::accountBalance_OK(QJsonObject r_obj)
{
    auto accountBalance = r_obj.value("Balance").toString();
    QMessageBox::information(this, "Information", "User's Account Balance is: " +accountBalance);
    this->parentWidget()->show();
    // delete this;
}

void AccountBalance::ServerError_error()
{
QMessageBox::critical(this, "critical", "Error on server can't access database");
}

void AccountBalance::noUsr_error()
{
    QMessageBox::critical(this, "Critical", "User  not found!");
}

AccountBalance::~AccountBalance()
{
    delete ui;
}



void AccountBalance::on_close_btn_clicked()
{
    this->parentWidget()->show();
    delete this;
}


void AccountBalance::on_Search_btn_clicked()
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
        l_obj.insert("RequestID","2");
        QJsonDocument l_doc(l_obj);
        QByteArray l_request = l_doc.toJson(QJsonDocument::JsonFormat::Indented);
        qInfo() << "Emitting signal from GetAccount to admin.";

        emit AB_General_Signal(l_request);
    }
}

void AccountBalance::on_numBox_textChanged(const QString &arg1)
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
