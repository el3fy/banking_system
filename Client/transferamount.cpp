#include "transferamount.h"
#include "ui_transferamount.h"

TransferAmount::TransferAmount(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransferAmount)
{
    ui->setupUi(this);
    num1_Regx.setPattern("^\\d{1,5}$");
    num2_Regx.setPattern("^\\d{1,5}$");
    amountRegx.setPattern("^(?!0*(?:10{7}|[1-9]\\d{6,}))\\d{1,6}(?:\\.\\d+)?$");
    ui->numBox_1->setValidator(new QRegularExpressionValidator(num1_Regx,this));
    ui->numBox_2->setValidator(new QRegularExpressionValidator(num2_Regx,this));
    ui->amountBox->setValidator(new QRegularExpressionValidator(amountRegx, this));
}

void TransferAmount::TransferAmount_Action()
{
    qInfo() << "Transfer amount done successfully!";
    QMessageBox::information(this, "Information", "Transfer amount done successfully!");
}

void TransferAmount::ServerError_error()
{
    QMessageBox::critical(this, "critical", "Error on server can't access database");
}

void TransferAmount::InvalidTransaction_error()
{
    QMessageBox::critical(this, "critical", "Invalid transaction");
}

void TransferAmount::noUsr_error()
{
QMessageBox::critical(this, "Critical", "User  not found!");
}

TransferAmount::~TransferAmount()
{
    delete ui;
}

void TransferAmount::on_close_btn_clicked()
{
    this->parentWidget()->show();//temp
    delete this;//temp
}


void TransferAmount::on_trans_btn_clicked()
{
    QString usrAcountNum_1 = ui->numBox_1->text().trimmed();
    QString usrAcountNum_2 = ui->numBox_2->text().trimmed();

    QString usrAmount = ui->amountBox->text().trimmed();

    if(usrAcountNum_1.isEmpty() || usrAcountNum_1.isEmpty() || usrAmount.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please fill all wanted information.");
    }
    else if(!(ui->numBox_1->hasAcceptableInput() && ui->amountBox->hasAcceptableInput() && ui->numBox_2->hasAcceptableInput()))
    {
        QMessageBox::warning(this, "Warning", "Invalid input.");
    }
    else if(usrAcountNum_1 == usrAcountNum_2)
    {
        QMessageBox::warning(this, "Warning", "Can't transfer to the same account");
    }
    else
    {
        QJsonObject l_obj;
        l_obj.insert("AccountNumber_1",usrAcountNum_1);
        l_obj.insert("AccountNumber_2",usrAcountNum_2);
        l_obj.insert("Amount", usrAmount);
        l_obj.insert("RequestID","5");

        QJsonDocument l_doc(l_obj);
        QByteArray l_request(l_doc.toJson());
        qInfo() << "emit request to user class";
        //emit signal to User.
        emit TA_User_Signal(l_request);
    }
}


void TransferAmount::on_numBox_1_textChanged(const QString &arg1)
{
    if(ui->numBox_1->hasAcceptableInput() && !(ui->numBox_1->text().isEmpty()))
    {
        ui->numBox_1->setStyleSheet("QLineEdit{ color: green;}");
        ui->num_1_Chk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");

    }
    else
    {
        ui->numBox_1->setStyleSheet("QLineEdit{ color: red;}");
        ui->num_1_Chk->setStyleSheet("QLabel{color: red;}");
        ui->num_1_Chk->setText("Account number must be at least 1 number and not greater than 5 numbers");
    }
}

void TransferAmount::on_numBox_2_textChanged(const QString &arg1)
{
    if(ui->numBox_2->hasAcceptableInput() && !(ui->numBox_2->text().isEmpty()))
    {
        ui->numBox_2->setStyleSheet("QLineEdit{ color: green;}");
        ui->num_2_Chk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");

    }
    else
    {
        ui->numBox_2->setStyleSheet("QLineEdit{ color: red;}");
        ui->num_2_Chk->setStyleSheet("QLabel{color: red;}");
        ui->num_2_Chk->setText("Account number must be at least 1 number and not greater than 5 numbers");
    }
}


void TransferAmount::on_amountBox_textChanged(const QString &arg1)
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
        ui->amountChk->setText("amount must be positive and can't be zero");
    }
}











