#include "accountnumber.h"
#include "ui_accountnumber.h"

AccountNumber::AccountNumber(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccountNumber)
{
    ui->setupUi(this);
    usernameRegex.setPattern("^[a-zA-Z]{1}[a-zA-Z0-9]{2,7}$");   //username(must be 10 charachters at maximum).
    ui->nameBox->setValidator(new QRegularExpressionValidator(usernameRegex,this));
}

void AccountNumber::accountNum_OK(QJsonObject r_obj)
{
    auto accountNum = r_obj.value("AccountNumber").toString().trimmed();
    QMessageBox::information(this, "Information", "User's Account number is: " +accountNum);
    this->parentWidget()->show();
    // delete this;
}

void AccountNumber::ServerError_error()
{
    QMessageBox::critical(this, "critical", "Error on server can't access database");
}

void AccountNumber::noUsr_error()
{
QMessageBox::critical(this, "Critical", "User  not found!");
}

AccountNumber::~AccountNumber()
{
    delete ui;
}


void AccountNumber::on_srch_btn_clicked()
{
    if(ui->nameBox->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "User name can't be empty!");
    }
    else
    {
        QString usrName = ui->nameBox->text().trimmed();
        QJsonObject l_obj;
        l_obj.insert("UserName",usrName);
        l_obj.insert("RequestID","1");
        QJsonDocument l_doc(l_obj);
        QByteArray l_request = l_doc.toJson(QJsonDocument::JsonFormat::Indented);
        qInfo() << "Emitting signal from GetAccount to admin.";

        emit AN_General_Signal(l_request);
    }
}


void AccountNumber::on_back_btn_clicked()
{
    this->parentWidget()->show();
    delete this;
}

//validate User input.
void AccountNumber::on_nameBox_textChanged(const QString &arg1)
{
    if(ui->nameBox->hasAcceptableInput())
    {
        ui->nameBox->setStyleSheet("QLineEdit{ color: green;}");
        ui->nameChk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");
    }
    else
    {
        ui->nameBox->setStyleSheet("QLineEdit{ color: red;}");
        ui->nameChk->setStyleSheet("QLabel{color: red;}");
        ui->nameChk->setText("User name must be at least 3 letters and can't start with numbers");
    }
}

