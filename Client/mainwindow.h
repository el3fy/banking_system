#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRegularExpression>
#include <QRegularExpressionValidator>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    //error actions
    void ServerError_error();
    void wrongUsr_error();
    void noUsr_error();
    void disable_refresh();
    void enable_refresh();

    void disable_login();
    void enable_login();

    void closedSocket_MessageBox();
    void clear();
    ~MainWindow();

private slots:
    void on_loginBtn_clicked();

    void on_nameBox_textChanged(const QString &arg1);

    void on_passBox_textChanged(const QString &arg1);

    void on_refresh_btn_clicked();

signals:

    void sendRequest_mW_View(QByteArray);

    void RC_MW_View_signal(QString hostIP); //temp

private:
    Ui::MainWindow *ui;
    QRegularExpression usernameRegex;
    QRegularExpression passwordRegex;
};
#endif // MAINWINDOW_H
