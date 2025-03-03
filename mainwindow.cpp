#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
}

MainWindow::MainWindow(QString username, QWidget *parent) : QMainWindow(parent) {
    this->setProperty("username", username);
    setupUI();
}

MainWindow::MainWindow(QString username, QString password, QWidget *parent) : QMainWindow(parent) {
    this->setProperty("username", username);
    this->setProperty("password", password);
    setupUI();
}

void MainWindow::setupUI() {
    this->setWindowTitle("Visual Study AI-D");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainTitle = new QLabel("Welcome to the Visual Study AI-D!", this);
    mainSubtitle = new QLabel("To get started, upload a file containing your video or notes to generate an animated summary.", this);

    button_one = new QPushButton("Upload File (.mp4, .pdf, .docx, etc.)", this);
    button_one->setFixedSize(600, 100);

    errorLabel = new QLabel("", this);

    button_two = new QPushButton("Use Camera", this);
    button_two->setFixedSize(300, 50);

    return_button = new QPushButton("←", this);
    return_button->setFixedSize(300, 50);

    vlayout = new QVBoxLayout();

    vlayout->addWidget(return_button, 0, Qt::AlignLeft);
    vlayout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));
    vlayout->addWidget(mainTitle, 0, Qt::AlignHCenter);
    vlayout->addWidget(mainSubtitle, 0, Qt::AlignHCenter);
    vlayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed));
    vlayout->addWidget(button_one, 0, Qt::AlignHCenter);
    vlayout->addWidget(button_two, 0, Qt::AlignHCenter);
    vlayout->addWidget(errorLabel, 0, Qt::AlignHCenter);

    username = this->property("username").toString();

    if (!username.isEmpty()) {
        qDebug()<<"User "<<this->property("username").toString()<<" has logged in--> Main Window";
        button_three = new QPushButton("Profile", this);
        button_three->setFixedSize(300, 50);

        vlayout->addWidget(button_three, 0, Qt::AlignHCenter);
        vlayout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));

        QFont profilebuttonFont("Helvetica", 16, QFont::Light);
        button_three->setFont(profilebuttonFont);

        connect(button_three, &QPushButton::released, this, &MainWindow::handleProfileButton);
    }

    centralWidget->setLayout(vlayout);

    // fonts
    QFont maintitleFont("Helvetica", 50, QFont::Bold);
    mainTitle->setFont(maintitleFont);

    QFont mainsubtitleFont("Helvetica", 20, QFont::Medium);
    mainSubtitle->setFont(mainsubtitleFont);

    QFont buttonFont("Helvetica", 16, QFont::Light);
    button_one->setFont(buttonFont);
    button_two->setFont(buttonFont);

    QFont uploaderrorFont("Helvetica", 14, QFont::StyleItalic);
    errorLabel->setFont(uploaderrorFont);

    QFont returnbuttonFont("Helvetica", 16, QFont::Medium);
    return_button->setFont(returnbuttonFont);

    // Connect
    connect(button_one, &QPushButton::released, this, &MainWindow::handleUploadButton);
    connect(button_two, &QPushButton::released, this, &MainWindow::handleCameraButton);
    connect(return_button, &QPushButton::released, this, &MainWindow::handleReturn);
}

void MainWindow::handleUploadButton() {
    QString filePath = QFileDialog::getOpenFileName(this,
        "Select a File",
        "",
        "Images (*.png *.jpg *.jpeg);;Videos (*.mp4 *.mov *.avi);;Documents (*.pdf *.doc *.docx *.txt);;All Files (*.*)");

    if (filePath.isEmpty()) {
        errorLabel->setText("No file selected.");
        return;
    } else {
        errorLabel->setText("Selected File: " + filePath);

        if (!this->property("username").isNull()){
            previewWindow = new previewwindow(this->property("username").toString(), filePath, this);
        } else {
            previewWindow = new previewwindow(this);
        }
        previewWindow->previousWindow = this;
        previewWindow->showMaximized();
        this->hide();
    }
}

void MainWindow::handleCameraButton() {
    if (cameraWindow) {
        cameraWindow->deleteLater();
    }
    if (!this->property("username").isNull()){
        cameraWindow = new CameraWindow(this->property("username").toString(), this);
    } else {
        cameraWindow = new CameraWindow(this);
    }
    cameraWindow = new CameraWindow(this);
    cameraWindow->previousWindow = this;
    cameraWindow->showMaximized();
    this->hide();
}

void MainWindow::handleProfileButton() {
    QString username = this->property("username").toString();

    if (profileWindow) {
        profileWindow->deleteLater();
    }
    profileWindow = new profilewindow(&username, this);
    profileWindow->previousWindow = this;
    profileWindow->showMaximized();
    this->hide();
}

void MainWindow::handleReturn(){
    if (previousWindow) {
        previousWindow->show();
        this->close();
    }
}
