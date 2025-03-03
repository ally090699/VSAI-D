#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFont>
#include <QGuiApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "loginwindow.h"

class homewindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit homewindow(QWidget *parent = nullptr);
    QWidget* previousWindow;
private slots:
    void handleSignInButton();
    void handleGetStartedButton();

private:
    QVBoxLayout *layout;
    QLabel *mainTitle;
    QLabel *mainSubtitle;
    QPushButton *signin_button;
    QPushButton *getstarted_button;
    MainWindow *mainWindow;
    loginwindow *loginWindow;
};

#endif // HOMEWINDOW_H
