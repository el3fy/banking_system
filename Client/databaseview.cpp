#include "databaseview.h"
#include "ui_databaseview.h"

DatabaseView::DatabaseView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DatabaseView)
{
    ui->setupUi(this);
}

void DatabaseView::dbView_OK(QJsonObject l_response)
{
    // QMessageBox::information(this, "Info", "welocme back!");
    l_response.remove("ResponseID");
    QJsonDocument l_doc(l_response);
    QByteArray dbData = l_doc.toJson(QJsonDocument::JsonFormat::Indented);
    QString txtData = QString::fromUtf8(dbData);
    ui->dataBase_text->clear();
    ui->dataBase_text->setText(txtData);
    qInfo() << "Database viewed sucessfully!";
}

void DatabaseView::ServerError_error()
{
    QMessageBox::critical(this, "critical", "Error on server can't access database");
}

DatabaseView::~DatabaseView()
{
    delete ui;
}

void DatabaseView::on_closeBtn_clicked()
{
    this->parentWidget()->show();//temp
    delete this;//temp
}


void DatabaseView::on_refreshBtn_clicked()
{
    QJsonObject l_obj;
    l_obj.insert("RequestID","6");

    QJsonDocument l_doc(l_obj);
    QByteArray l_request(l_doc.toJson());
    qInfo() << "emit request to admin class";
    //emit signal to admin.
    emit DB_Admin_Signal(l_request);
}

