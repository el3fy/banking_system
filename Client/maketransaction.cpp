#include "maketransaction.h"
#include "ui_maketransaction.h"

makeTransaction::makeTransaction(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::makeTransaction)
{
    ui->setupUi(this);
    numRegx.setPattern("^\\d{1,5}$");
    amountRegx.setPattern("^[+-](?!0\\d)\\d{1,7}(\\.\\d+)?$");
    ui->numBox->setValidator(new QRegularExpressionValidator(numRegx,this));
    ui->amountBox->setValidator(new QRegularExpressionValidator(amountRegx, this));
}

void makeTransaction::makeTransaction_Action(QJsonObject r_obj)
{
    QMessageBox::information(this, "information", "Transaction made successfully");
}

void makeTransaction::ServerError_error()
{
    QMessageBox::critical(this, "critical", "Error on server can't access database");
}

void makeTransaction::InvalidTransaction_error()
{
    QMessageBox::critical(this, "critical", "Invalid transaction");
}

void makeTransaction::noUsr_error()
{
QMessageBox::critical(this, "Critical", "User  not found!");
}

makeTransaction::~makeTransaction()
{
    delete ui;
}




void makeTransaction::on_close_btn_clicked()
{
    this->parentWidget()->show();
    delete this;
}


void makeTransaction::on_makeTrans_btn_clicked()
{
    QString usrAcountNum = ui->numBox->text().trimmed();
    QString usrAmount = ui->amountBox->text().trimmed();

    if(usrAcountNum.isEmpty() || usrAmount.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please fill all wanted information.");
    }
    else if(!(ui->numBox->hasAcceptableInput() && ui->amountBox->hasAcceptableInput()))
    {
        QMessageBox::warning(this, "Warning", "Invalid input.");
    }
    else
    {
        QJsonObject l_obj;
        l_obj.insert("AccountNumber",usrAcountNum);
        l_obj.insert("Amount", usrAmount);
        l_obj.insert("RequestID","4");

        QJsonDocument l_doc(l_obj);
        QByteArray l_request(l_doc.toJson());
        qInfo() << "emit request to user class";
        //emit signal to User.
        emit MT_User_Signal(l_request);
    }
}


void makeTransaction::on_numBox_textChanged(const QString &arg1)
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


void makeTransaction::on_amountBox_textChanged(const QString &arg1)
{
    if(ui->amountBox->hasAcceptableInput() && !(ui->amountBox->text().isEmpty()))
    {
        ui->amountBox->setStyleSheet("QLineEdit{ color: green;}");
        ui->amountChk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");
    }
    else
    {
        ui->amountBox->setStyleSheet("QLineEdit{ color: red;}");
        ui->amountChk->setStyleSheet("QLabel{color: red;}");
        ui->amountChk->setText("amount must begain with + or -");
    }
}

