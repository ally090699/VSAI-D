#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QMainWindow>
#include <QMediaCaptureSession>
#include <QVideoWidget>
#include <QCamera>
#include <QMediaDevices>
#include <QVBoxLayout>
#include <QComboBox>

class CameraWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit CameraWindow(QWidget *parent = nullptr);
    ~CameraWindow();
    bool checkCameraPermission();

private:
    QMediaCaptureSession captureSession;
    QCamera *camera;
    QComboBox *cameraSelector;
    QVideoWidget *videoWidget;

    bool isAuthorized();
    void setupCamera(const QCameraDevice &device);
};

#endif // CAMERAWINDOW_H
