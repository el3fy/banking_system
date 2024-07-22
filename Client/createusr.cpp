#include "createusr.h"
#include "ui_createusr.h"

CreateUsr::CreateUsr(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CreateUsr)
{
    ui->setupUi(this);

    QRegularExpression usernameRegex("^[a-zA-Z]{3,10}[a-zA-Z0-9]{0,7}$");
    QRegularExpression passwordRegex("^[a-zA-Z0-9]{8}$");
    QRegularExpression fullNameRegex("^[a-zA-Z]{1,20} [a-zA-Z]{1,20}$");
    QRegularExpression userAgeRegex("^(1[8-9]|[2-9][0-9])$");

    ui->usrName_lineEdit->setValidator(new QRegularExpressionValidator(usernameRegex,this));
    ui->usrPass_lineEdit->setValidator(new QRegularExpressionValidator(passwordRegex, this));
    ui->fullName_lineEdit->setValidator(new QRegularExpressionValidator(fullNameRegex,this));
    ui->usrAge_lineEdit->setValidator(new QRegularExpressionValidator(userAgeRegex, this));

    connect(ui->usrName_lineEdit, &QLineEdit::textChanged, this, &CreateUsr::checkInput);
    connect(ui->usrPass_lineEdit, &QLineEdit::textChanged, this, &CreateUsr::checkInput);
    connect(ui->fullName_lineEdit, &QLineEdit::textChanged, this, &CreateUsr::checkInput);
    connect(ui->usrAge_lineEdit, &QLineEdit::textChanged, this, &CreateUsr::checkInput);
}

void CreateUsr::ServerError_error()
{
    QMessageBox::critical(this, "critical", "Error on server can't access database");
}

void CreateUsr::existUsr_error()
{
    QMessageBox::critical(this, "Critical", "Can't create a user name because it's already reserved");
}

void CreateUsr::CreateUsr_OK()
{
    QMessageBox::information(this, "Information", "A new user has been created successfully!");
    this->close();
}

void CreateUsr::checkInput()
{
    if(ui->usrName_lineEdit->hasAcceptableInput())
    {
        ui->usrName_lineEdit->setStyleSheet("QLineEdit{ color: green;}");
        ui->name_chk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");
    }
    else
    {
        ui->usrName_lineEdit->setStyleSheet("QLineEdit{ color: red;}");
        ui->name_chk->setStyleSheet("QLabel{color: red;}");
        ui->name_chk->setText("User name must be at least 3 letters and can't start with numbers");
    }

    if(ui->usrPass_lineEdit->hasAcceptableInput())
    {
        ui->usrPass_lineEdit->setStyleSheet("QLineEdit{ color: green;}");
        ui->password_chk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");
    }
    else
    {
        ui->usrPass_lineEdit->setStyleSheet("QLineEdit{ color: red;}");
        ui->password_chk->setStyleSheet("QLabel{color: red;}");
        ui->password_chk->setText("pasword must be 8 charachters");
    }

    if(ui->fullName_lineEdit->hasAcceptableInput())
    {
        ui->fullName_lineEdit->setStyleSheet("QLineEdit{ color: green;}");
        ui->fullName_chk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");
    }
    else
    {
        ui->fullName_lineEdit->setStyleSheet("QLineEdit{ color: red;}");
        ui->fullName_chk->setStyleSheet("QLabel{color: red;}");
        ui->fullName_chk->setText("the full name must have white space");
    }

    if(ui->usrAge_lineEdit->hasAcceptableInput())
    {
        ui->usrAge_lineEdit->setStyleSheet("QLineEdit{ color: green;}");
        ui->age_chk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");
    }
    else
    {
        ui->usrAge_lineEdit->setStyleSheet("QLineEdit{ color: red;}");
        ui->age_chk->setStyleSheet("QLabel{color: red;}");
        ui->age_chk->setText("User must be 18 to create an account.");
    }
}

CreateUsr::~CreateUsr()
{
    delete ui;
}

void CreateUsr::on_createUsr_btn_clicked()
{
    QString usrName = ui->usrName_lineEdit->text().trimmed();
    QString usrAge = ui->usrAge_lineEdit->text().trimmed();
    QString fullName = ui->fullName_lineEdit->text().trimmed();
    QString usrPass = ui->usrPass_lineEdit->text().trimmed();

    if(usrName.isEmpty() || usrPass.isEmpty() || fullName.isEmpty() || usrAge.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please fill all wanted information.");
    }
    else if(!(ui->usrName_lineEdit->hasAcceptableInput() && ui->usrAge_lineEdit->hasAcceptableInput() && ui->fullName_lineEdit->hasAcceptableInput() && ui->usrPass_lineEdit->hasAcceptableInput()))
    {
        QMessageBox::warning(this, "Warning", "Invalid input.");
    }
    else
    {
        QJsonObject l_obj;
        l_obj.insert("UserName",usrName);
        l_obj.insert("FullName",fullName);
        l_obj.insert("Age",usrAge);
        l_obj.insert("Password",usrPass);
        l_obj.insert("IsAdmin", ui->checkBox->isChecked());
        l_obj.insert("Balance", "0");
        l_obj.insert("RequestID","7");

        QJsonDocument l_doc(l_obj);
        QByteArray l_request(l_doc.toJson());
        qInfo() << "emit request to admin class";
        //emit signal to admin.
        emit CU_Admin_Signal(l_request);
    }
}


void CreateUsr::on_pushButton_clicked()
{
    this->parentWidget()->show();//temp
    delete this;//temp
}

