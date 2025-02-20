#include "camerawindow.h"
#import <AVFoundation/AVFoundation.h>

CameraWindow::CameraWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Camera Capture");

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Camera selection dropdown
    cameraSelector = new QComboBox(this);
    auto cameras = QMediaDevices::videoInputs();
    for (const auto &device : cameras) {
        cameraSelector->addItem(device.description(), QVariant::fromValue(device));
    }

    connect(cameraSelector, &QComboBox::currentIndexChanged, this, [=](int index) {
      if (index>=0){
        setupCamera(cameras[index]);
      }
    });

    videoWidget = new QVideoWidget(this);
    layout->addWidget(cameraSelector);
    layout->addWidget(videoWidget);

    if (!cameras.isEmpty()) {
        setupCamera(cameras.first());
    }
}

bool CameraWindow::checkCameraPermission() {
auto cameras = QMediaDevices::videoInputs();
    if (cameras.isEmpty()) {
        qWarning() << "No cameras found.";
        return false;
    }

    return true;
}

bool CameraWindow::isAuthorized() {
    AVAuthorizationStatus status = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];

    if (status == AVAuthorizationStatusAuthorized) {
        return true; // Already authorized
    }

    if (status == AVAuthorizationStatusNotDetermined) {
        __block bool accessGranted = false;
        dispatch_semaphore_t semaphore = dispatch_semaphore_create(0); // Create a semaphore

        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
            accessGranted = granted;
            dispatch_semaphore_signal(semaphore); // Signal completion
        }];

        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER); // Wait for permission result
        return accessGranted;
    }

    return false; // Denied or restricted
}

CameraWindow::~CameraWindow() {
    // Stop the camera if it's running
    if (camera) {
        camera->stop();  // Stop the camera
        delete camera;   // Delete the camera object to free up memory
    }
    delete videoWidget;
}

void CameraWindow::setupCamera(const QCameraDevice &device) {
    if (!isAuthorized()) {
        qWarning() << "Camera access is not authorized!";
        return;
    }

    if (!checkCameraPermission()) {
        qWarning() << "Camera permission not granted!";
        return;
    }

    camera = new QCamera(device, this);
    camera->setCameraDevice(device);
    camera->setActive(true);
    captureSession.setCamera(camera);
    captureSession.setVideoOutput(videoWidget);
    camera->start();
}
