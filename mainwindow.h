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
#include <QTimer>
#include <QHBoxLayout>

#include "profilewindow.h"
#include "previewwindow.h"
#include "camerawindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(QString username, QWidget *parent = nullptr);
    MainWindow(QString username, QString password, QWidget *parent = nullptr);
    QWidget* previousWindow;
private slots:
    void handleUploadButton();
    void handleCameraButton();
    void handleProfileButton();
    void setupUI();
    void handleReturn();

private:
    QVBoxLayout *vlayout;
    QLabel *mainTitle;
    QLabel *mainSubtitle;
    QPushButton *button_one;
    QPushButton *button_two;
    QPushButton *button_three;
    QPushButton *return_button;
    QLabel *errorLabel;
    previewwindow *previewWindow;
    MainWindow *mainWindow;
    profilewindow *profileWindow;
    CameraWindow *cameraWindow;
    QString username;
};
#endif // MAINWINDOW_H
