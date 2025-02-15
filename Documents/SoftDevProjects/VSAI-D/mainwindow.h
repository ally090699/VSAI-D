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

class previewwindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private slots:
    void handleUploadButton();
    void handleCameraButton();

private:
    QVBoxLayout *layout;
    QLabel *mainTitle;
    QLabel *mainSubtitle;
    QPushButton *upload_button;
    QLabel *upload_error;
    QPushButton *camera_button;
    CameraWindow *cameraWindow;
    previewwindow *previewWindow;
};
#endif // MAINWINDOW_H
