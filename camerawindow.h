#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

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

#include "computervision.h"
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include "videowindow.h"

class CameraWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CameraWindow(QWidget *parent = nullptr);
    CameraWindow(QString username, QWidget *parent = nullptr);
    QWidget* previousWindow;

private slots:
    void setupUI();
    void stopCamera();
    void startTextRecognition();
    void stopTextRecognition();
    void startCamera();
    void processFrame();
    void handleReturn();
    void handleNext();

private:
    QVBoxLayout *vlayout;
    QLabel *mainSubtitle1;
    QLabel *mainSubtitle2;
    QLabel *mainSubtitle3;
    QPushButton *button_one;
    QPushButton *button_two;
    QPushButton *button_three;
    QPushButton *button_four;
    QPushButton *return_button;
    QPushButton *next_button;
    QLabel *errorLabel;
    VideoWindow *videoWindow;

    QLabel *videoPane;
    ComputerVision *cve;
    QHBoxLayout *hlayout;

    QTimer *timer;
    cv::VideoCapture cap;
    cv::Mat frame;
    int deviceID;
    int apiID;
};
#endif // CAMERAWINDOW_H
