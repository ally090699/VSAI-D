#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFont>
#include <QDebug>
#include <QGuiApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCryptographicHash>

#include "mainwindow.h"

class loginwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit loginwindow(QWidget *parent = nullptr);
    QWidget* previousWindow;
private slots:
    void handleRegisterButton();
    void handleLoginButton();
    void connectDatabase();
    bool insertUser(const QString& username, const QString& password);
    bool authenticateUser(const QString& username, const QString& password);
    void handleReturn();
private:
    QVBoxLayout *layout;
    QLabel *mainTitle;
    QLabel *mainSubtitle;
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QPushButton *register_button;
    QPushButton *login_button;
    QPushButton *return_button;
    QLabel *login_error;
    MainWindow *mainWindow;
    QCryptographicHash *hashedPassword;
    QSqlDatabase db;
};

#endif // LOGINWINDOW_H
