#include "transhistory.h"
#include "ui_transhistory.h"

TransHistory::TransHistory(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TransHistory)
{
    ui->setupUi(this);

    numRegx.setPattern("^\\d{1,5}$");
    countRegx.setPattern("^(?!0*(?:10{7}|[1-9]\\d{6,}))\\d{1,6}(?:\\.\\d+)?$");
    ui->numBox->setValidator(new QRegularExpressionValidator(numRegx,this));
    ui->countBox->setValidator(new QRegularExpressionValidator(countRegx, this));
    ui->tableWidget->setRowCount(200);
}

void TransHistory::TransactionHistory_action(QJsonObject l_response)
{
    ui->tableWidget->clear();
    QJsonArray l_array(l_response.value("TransactionHistory").toArray());
    qInfo() << "the size of array is: " << l_array.count();
    for(int i = 0; i < l_array.count(); i++)
    {
        QString date = l_array.at(i).toObject().value("date").toString();
        double amount = l_array.at(i).toObject().value("amount").toDouble();

        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(amount)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(date));
    }

    qInfo() << "Database viewed sucessfully!";
}

void TransHistory::ServerError_error()
{
    QMessageBox::critical(this, "critical", "Error on server can't access database");
}

void TransHistory::noUsr_error()
{
QMessageBox::critical(this, "Critical", "User  not found!");
}

TransHistory::~TransHistory()
{
    delete ui;
}

void TransHistory::on_close_btn_clicked()
{
    this->parentWidget()->show();//temp
    delete this;//temp
}


void TransHistory::on_numBox_textChanged(const QString &arg1)
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


void TransHistory::on_countBox_textChanged(const QString &arg1)
{
    if(ui->countBox->hasAcceptableInput() && !(ui->countBox->text().isEmpty()))
    {
        ui->countBox->setStyleSheet("QLineEdit{ color: green;}");
        ui->countChk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");
    }
    else
    {
        ui->countBox->setStyleSheet("QLineEdit{ color: red;}");
        ui->countChk->setStyleSheet("QLabel{color: red;}");
        ui->countChk->setText("amount must begain with + or -");
    }
}

void TransHistory::on_view_btn_clicked()
{
    QString usrAcountNum = ui->numBox->text().trimmed();
    QString Count = ui->countBox->text().trimmed();

    if(usrAcountNum.isEmpty() || Count.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please fill all wanted information.");
    }
    else if(!(ui->numBox->hasAcceptableInput() && ui->countBox->hasAcceptableInput()))
    {
        QMessageBox::warning(this, "Warning", "Invalid input.");
    }
    else
    {
        QJsonObject l_obj;
        l_obj.insert("AccountNumber",usrAcountNum);
        l_obj.insert("Count", Count);
        l_obj.insert("RequestID","3");

        QJsonDocument l_doc(l_obj);
        QByteArray l_request(l_doc.toJson());
        qInfo() << "emit request to user class";


        emit TH_General_Signal(l_request);

    }
}

