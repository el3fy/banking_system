#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    usernameRegex.setPattern("^[a-zA-Z]{1}[a-zA-Z0-9]{2,7}$");   //username(must be 8 charachters at maximum).
    passwordRegex.setPattern("^[a-zA-Z0-9]{8}$");   //password(must be 8 charachters at maximum).

    QPixmap pix(":/img/img/logo.png"); //To set the logo on the opening screen.
    ui->logoLbl->setPixmap(pix.scaled(300,300,Qt::KeepAspectRatio));//to rander the logo.

    ui->nameBox->setValidator(new QRegularExpressionValidator(usernameRegex,this));
    ui->passBox->setValidator(new QRegularExpressionValidator(passwordRegex, this));
}

void MainWindow::ServerError_error()
{
    QMessageBox::critical(this, "critical", "Error on server can't access database");
}

void MainWindow::wrongUsr_error()
{
    QMessageBox::critical(this, "Critical", "Wrong password");
}

void MainWindow::noUsr_error()
{
    QMessageBox::critical(this, "Critical", "User  not found!");
}

void MainWindow::disable_refresh()
{
    if(ui->refresh_btn->isEnabled())
    {
        ui->refresh_btn->setDisabled(true);
        ui->loginBtn->setEnabled(true);

        qInfo() << "Refresh button has disabled successfully";
    }
}

void MainWindow::enable_refresh()
{
    ui->refresh_btn->setEnabled(true);
     ui->loginBtn->setDisabled(true);//temp
    qInfo() << "Refresh button has enabled successfully";
}

void MainWindow::disable_login()
{
    ui->loginBtn->setDisabled(true);
    ui->refresh_btn->setEnabled(true);//temp
}

void MainWindow::enable_login()
{
    ui->loginBtn->setEnabled(true);
    ui->refresh_btn->setDisabled(true);//temp
}

void MainWindow::closedSocket_MessageBox()
{
    QMessageBox::critical(this, "Critical", "Can't connect to server!");
    ui->loginBtn->setDisabled(true);
}

void MainWindow::clear()
{
    ui->nameBox->clear();
    ui->passBox->clear();
}

MainWindow::~MainWindow()
{
    qInfo() << "mainWindow will emits signal to view to destroy all";

    delete ui;
}

void MainWindow::on_loginBtn_clicked()
{
    QString usrName = ui->nameBox->text().trimmed();
    QString usrPass = ui->passBox->text().trimmed();
    QString hostIP = ui->ipBox->text().trimmed();
    if(usrName.isEmpty() || usrPass.isEmpty() || hostIP.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please fill all wanted information.");
    }
    else if(!(ui->nameBox->hasAcceptableInput() && ui->passBox->hasAcceptableInput()))
    {
        QMessageBox::warning(this, "Warning", "Invalid input.");
    }
    else
    {
        QJsonObject l_obj;
        l_obj.insert("UserName", usrName);
        l_obj.insert("Password",usrPass);
        l_obj.insert("RequestID",0); // zero is request ID of login.
        QJsonDocument l_doc(l_obj);
        QByteArray l_request = l_doc.toJson(QJsonDocument::JsonFormat::Indented);
        emit sendRequest_mW_View(l_request);  //sending request to View class
    }
}

//validate User input.
void MainWindow::on_nameBox_textChanged(const QString &arg1)
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


void MainWindow::on_passBox_textChanged(const QString &arg1)
{
    if(ui->passBox->hasAcceptableInput())
    {
        ui->passBox->setStyleSheet("QLineEdit{ color: green;}");
        ui->passChk->setStyleSheet("QLabel{color: rgb(36, 68, 67);}");
    }
    else
    {
        ui->passBox->setStyleSheet("QLineEdit{ color: red;}");
        ui->passChk->setStyleSheet("QLabel{color: red;}");
        ui->passChk->setText("pasword must be 8 charachters");
    }
}



void MainWindow::on_refresh_btn_clicked()
{
    QString hostIP = ui->ipBox->text().trimmed();
    //emit to View
    emit RC_MW_View_signal(hostIP);
}


