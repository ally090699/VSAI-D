#include "camerawindow.h"

CameraWindow::CameraWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
}

CameraWindow::CameraWindow(QString username, QWidget *parent) : QMainWindow(parent) {
    this->setProperty("username", username);
    setupUI();
}

void CameraWindow::setupUI(){
    qDebug()<<"setupUI enter.";
    this->setWindowTitle("Camera Capture");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainSubtitle1 = new QLabel("Begin by starting the camera and setting up your environment, before holding up your notes or any document you'd like to scan.", this);
    mainSubtitle2 = new QLabel("When you're ready to start capturing text, toggle 'Start/Stop Text Recognition'. The text captured will appear in the editor to the right.", this);
    mainSubtitle3 = new QLabel("Once you are done capturing text, click 'Next", this);

    button_one = new QPushButton("Start Text Recognition", this);
    button_one->setFixedSize(400, 50);

    button_two = new QPushButton("Stop Text Recognition", this);
    button_two->setFixedSize(400, 50);

    errorLabel = new QLabel("", this);

    button_three = new QPushButton("Start Camera", this);
    button_three->setFixedSize(150, 50);

    button_four = new QPushButton("Stop Camera", this);
    button_four->setFixedSize(150, 50);

    videoPane = new QLabel(this);
    videoPane->setFixedSize(1200, 650);

    return_button = new QPushButton("←", this);
    return_button->setFixedSize(50, 50);

    next_button = new QPushButton("Next", this);
    next_button->setFixedSize(75, 50);

    hlayout = new QHBoxLayout();
    vlayout = new QVBoxLayout();

    hlayout->addWidget(button_one, 0);
    hlayout->addWidget(button_two, 0);
    hlayout->addWidget(button_three, 0);
    hlayout->addWidget(button_four, 0);

    vlayout->addWidget(return_button, 0, Qt::AlignLeft);
    vlayout->addWidget(mainSubtitle1, 0, Qt::AlignHCenter);
    vlayout->addWidget(mainSubtitle2, 0, Qt::AlignHCenter);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(videoPane, 0, Qt::AlignHCenter);
    vlayout->addWidget(next_button, 0, Qt::AlignRight);
    vlayout->addWidget(errorLabel, 0, Qt::AlignHCenter);

    centralWidget->setLayout(vlayout);

    // fonts

    QFont returnbuttonFont("Helvetica", 16, QFont::Medium);
    return_button->setFont(returnbuttonFont);
    next_button->setFont(returnbuttonFont);

    QFont mainsubtitleFont("Helvetica", 18, QFont::Medium);
    mainSubtitle1->setFont(mainsubtitleFont);
    mainSubtitle2->setFont(mainsubtitleFont);

    QFont buttonGroupFont("Helvetica", 16, QFont::Light);
    button_one->setFont(buttonGroupFont);
    button_two->setFont(buttonGroupFont);
    button_three->setFont(buttonGroupFont);
    button_four->setFont(buttonGroupFont);

    QFont uploaderrorFont("Helvetica", 14, QFont::StyleItalic);
    errorLabel->setFont(uploaderrorFont);

    // Connect
    connect(button_one, &QPushButton::released, this, &CameraWindow::startTextRecognition);
    connect(button_two, &QPushButton::released, this, &CameraWindow::stopTextRecognition);
    connect(button_three, &QPushButton::released, this, &CameraWindow::startCamera);
    connect(button_four, &QPushButton::released, this, &CameraWindow::stopCamera);
    connect(return_button, &QPushButton::released, this, &CameraWindow::handleReturn);
    connect(next_button, &QPushButton::released, this, &CameraWindow::handleNext);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CameraWindow::processFrame);
    qDebug()<<"setupUI exit.";
}

void CameraWindow::processFrame(){
    qDebug()<<"ProcessFrame enter.";
    cap >> frame;

    if (frame.empty()){
        qDebug()<<"Empty frame captured.";
    }

    cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
    QImage img((const unsigned char*)frame.data, frame.cols, frame.rows, frame.step, QImage::Format_Grayscale8);
    videoPane->setPixmap(QPixmap::fromImage(img));
    qDebug()<<"ProcessFrame exit.";
}

void CameraWindow::startTextRecognition(){
    qDebug()<<"startTextRecognition enter.";

    if (!cve) {
        qDebug() << "Error: cve is NULL!";
        return;
    }

    std::string extractedText = cve->extractTextFromImage(frame);
    if (!extractedText.empty()){
        qDebug() << "Extracted Text: " << QString::fromStdString(extractedText);
    }
    qDebug()<<"startTextRecognition exit.";
}

void CameraWindow::stopTextRecognition() {
    qDebug() << "stopTextRecognition enter.";

    if (cve) {
        cve->clearOCR();
    }

    qDebug() << "Text recognition stopped.";
    qDebug() << "stopTextRecognition exit.";
}


void CameraWindow::stopCamera(){
    qDebug()<<"stopCamera enter.";
    if (cap.isOpened()){
        cap.release();
    }
    timer->stop();
    qDebug()<<"stopCamera exit.";
}

void CameraWindow::startCamera(){
    qDebug()<<"startCamera enter.";
    if (!cap.isOpened()) {
        deviceID = 0;
        apiID = cv::CAP_ANY;
        if (cap.open(deviceID, apiID)) {
            qDebug() << "Camera started successfully!";
            timer->start(30);
        } else {
            qDebug() << "Error! Unable to open camera.";
        }
    }
    qDebug()<<"startCamera exit.";
}

void CameraWindow::handleReturn(){
    if (previousWindow) {
        previousWindow->show();
        this->close();
    }
}

void CameraWindow::handleNext(){
    if (!this->property("username").isNull()){
        videoWindow = new VideoWindow(this->property("username").toString(), this);
    } else {
        videoWindow = new VideoWindow(this);
    }
    videoWindow->previousWindow = this;
    videoWindow->showMaximized();
    this->hide();
}
