#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFont>
#include <QGuiApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>

#include "camerawindow.h"
#include "profilewindow.h"
#include "previewwindow.h"
#include "loginwindow.h"

class previewwindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(QString username, QString password, QWidget *parent = nullptr);
private slots:
    void handleUploadButton();
    void handleCameraButton();
    void handleProfileButton();
    void handleSignInButton();
    void setupUI();

private:
    QVBoxLayout *layout;
    QLabel *mainTitle;
    QLabel *mainSubtitle;
    QPushButton *upload_button;
    QLabel *upload_error;
    QPushButton *camera_button;
    CameraWindow *cameraWindow;
    previewwindow *previewWindow;
    MainWindow *mainWindow;
    profilewindow *profileWindow;
    QPushButton *profile_button;
    QPushButton *signin_button;
    loginwindow *loginWindow;
};
#endif // MAINWINDOW_H
