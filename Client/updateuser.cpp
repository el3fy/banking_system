#include "updateuser.h"
#include "ui_updateuser.h"

UpdateUser::UpdateUser(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateUser)
{
    ui->setupUi(this);

    numRegx.setPattern("^\\d{1,5}$");
    usrnameRegx.setPattern("^[a-zA-Z][a-zA-Z0-9]{2,9}$");
    fullNameRegx.setPattern("^[a-zA-Z]{1,20} [a-zA-Z]{1,20}$");
    passwordRegx.setPattern("^.{8}$");
    ageRegx.setPattern("^(1[8-9]|[2-9][0-9])$");

    ui->nameBox->setValidator(new QRegularExpressionValidator(usrnameRegx,this));
    ui->PassBox->setValidator(new QRegularExpressionValidator(passwordRegx, this));

    ui->numBox->setValidator(new QRegularExpressionValidator(numRegx,this));
    ui->FullBox->setValidator(new QRegularExpressionValidator(fullNameRegx, this));
    ui->AgeBox->setValidator(new QRegularExpressionValidator(ageRegx, this));
}

void UpdateUser::UpdateUsr_OK()
{
    QMessageBox::information(this, "Information", "User's data has been updated successfully");
    // this->close();
}

void UpdateUser::ServerError_error()
{
    QMessageBox::critical(this, "critical", "Error on server can't access database");
}

void UpdateUser::noUsr_error()
{
QMessageBox::critical(this, "Critical", "User  not found!");
}

void UpdateUser::existUsr_error()
{
    QMessageBox::critical(this, "Critical", "Can't update user name to this name becaues this name is reserved");
}

UpdateUser::~UpdateUser()
{
    delete ui;
}

void UpdateUser::on_update_Btn_clicked()
{
    if(ui->numBox->text().isEmpty())
    {
        qWarning() << "Can't update without specifying user's Account number.";
        QMessageBox::warning(this, "Warning", "You've to enter user's account number");
    }
    else
    {
        QJsonObject l_obj;
        if(!(ui->nameBox->text().isEmpty()) && ui->nameBox->hasAcceptableInput())
        {
            qInfo() << "User name will be updated";
            QString usrName = ui->nameBox->text().trimmed();
            l_obj.insert("UserName", usrName);
        }
        if(!(ui->AgeBox->text().isEmpty()) && ui->AgeBox->hasAcceptableInput())
        {
            qInfo() << "User age will be updated";
            QString usrAge = ui->AgeBox->text().trimmed();
            l_obj.insert("Age", usrAge);
        }
        if(!(ui->FullBox->text().isEmpty()) && ui->FullBox->hasAcceptableInput())
        {
            qInfo() << "User full name will be updated";
            QString usrFull = ui->FullBox->text().trimmed();
            l_obj.insert("FullName", usrFull);
        }
        if(!(ui->PassBox->text().isEmpty()) && ui->PassBox->hasAcceptableInput())
        {
            qInfo() << "User password will be updated";
            QString usrPass = ui->PassBox->text().trimmed();
            l_obj.insert("Password", usrPass);
        }
        QString accountNum =  ui->numBox->text().trimmed();
        l_obj.insert("RequestID","9");
        l_obj.insert("AccountNumber",accountNum);
        QJsonDocument l_doc(l_obj);
        QByteArray l_request = l_doc.toJson(QJsonDocument::JsonFormat::Indented);

        emit UU_Admin_Signal(l_request);
        qInfo() << "user updated successfully";
    }
}


void UpdateUser::on_Close_btn_clicked()
{
    this->parentWidget()->show();
    delete this;
}


void UpdateUser::on_numBox_textChanged(const QString &arg1)
{
    if(ui->numBox->hasAcceptableInput() && !(ui->numBox->text().isEmpty()))
    {
        ui->numBox->setStyleSheet("QLineEdit{ color: green;}");
        ui->numChk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");

        ui->nameBox->setEnabled(true);
        ui->FullBox->setEnabled(true);
        ui->AgeBox->setEnabled(true);
        ui->PassBox->setEnabled(true);
        ui->update_Btn->setEnabled(true);
    }
    else
    {
        ui->numBox->setStyleSheet("QLineEdit{ color: red;}");
        ui->numChk->setStyleSheet("QLabel{color: red;}");
        ui->numChk->setText("Account number must be at least 1 number and not greater than 5 numbers");

        ui->nameBox->setEnabled(false);
        ui->FullBox->setEnabled(false);
        ui->AgeBox->setEnabled(false);
        ui->PassBox->setEnabled(false);
        ui->update_Btn->setEnabled(false);

    }
}


void UpdateUser::on_nameBox_textChanged(const QString &arg1)
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


void UpdateUser::on_FullBox_textChanged(const QString &arg1)
{
    if(ui->FullBox->hasAcceptableInput())
    {
        ui->FullBox->setStyleSheet("QLineEdit{ color: green;}");
        ui->fullChk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");
    }
    else
    {
        ui->FullBox->setStyleSheet("QLineEdit{ color: red;}");
        ui->fullChk->setStyleSheet("QLabel{color: red;}");
        ui->fullChk->setText("User's full name must have two parts and can't contain digits or special characters");
    }
}


void UpdateUser::on_AgeBox_textChanged(const QString &arg1)
{
    if(ui->AgeBox->hasAcceptableInput())
    {
        ui->AgeBox->setStyleSheet("QLineEdit{ color: green;}");
        ui->ageChk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");
    }
    else
    {
        ui->AgeBox->setStyleSheet("QLineEdit{ color: red;}");
        ui->ageChk->setStyleSheet("QLabel{color: red;}");
        ui->ageChk->setText("User age must be at leat 18 and can't be more than 99");
    }
}


void UpdateUser::on_PassBox_textChanged(const QString &arg1)
{
    if(ui->PassBox->hasAcceptableInput())
    {
        ui->PassBox->setStyleSheet("QLineEdit{ color: green;}");
        ui->passChk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");
    }
    else
    {
        ui->PassBox->setStyleSheet("QLineEdit{ color: red;}");
        ui->passChk->setStyleSheet("QLabel{color: red;}");
        ui->passChk->setText("User password must be at least 8 charachters");
    }
}

