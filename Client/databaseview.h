#ifndef DATABASEVIEW_H
#define DATABASEVIEW_H

#include <QDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

namespace Ui {
class DatabaseView;
}

class DatabaseView : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseView(QWidget *parent = nullptr);
    void dbView_OK(QJsonObject);

    //error actions
    void ServerError_error();
    ~DatabaseView();

signals:
    void DB_Admin_Signal(QByteArray);
private slots:
    void on_closeBtn_clicked();

    void on_refreshBtn_clicked();

private:
    Ui::DatabaseView *ui;
};

#endif // DATABASEVIEW_H
