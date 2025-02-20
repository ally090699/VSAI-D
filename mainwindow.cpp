#include "mainwindow.h"
#include "previewwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();

    signin_button = new QPushButton("Sign In", this);
    signin_button->setFixedSize(300, 50);
    layout->addWidget(signin_button, 0, Qt::AlignHCenter);
    connect(signin_button, &QPushButton::released, this, &MainWindow::handleSignInButton);
}

MainWindow::MainWindow(QString username, QString password, QWidget *parent) : MainWindow(parent) {
    this->setProperty("username", username);
    this->setProperty("password", password);

    if (!username.isEmpty()) {
        qDebug()<<"User "<<this->property("username").toString()<<" has logged in--> Main Window";
        profile_button = new QPushButton("Profile", this);
        profile_button->setFixedSize(300, 50);

        layout->addWidget(profile_button, 0, Qt::AlignHCenter);
        layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));

        connect(profile_button, &QPushButton::released, this, &MainWindow::handleProfileButton);
    }
}

void MainWindow::setupUI() {
    this->setWindowTitle("Visual Study AI-D");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainTitle = new QLabel("Welcome to the Visual Study AI-D!", this);
    mainSubtitle = new QLabel("To get started, upload a file containing your video or notes to generate an animated summary.", this);

    upload_button = new QPushButton("Upload File (.mp4, .pdf, .docx, etc.)", this);
    upload_button->setFixedSize(600, 100);

    upload_error = new QLabel("", this);

    camera_button = new QPushButton("Use Camera", this);
    camera_button->setFixedSize(300, 50);

    layout = new QVBoxLayout();

    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(mainTitle, 0, Qt::AlignHCenter);
    layout->addWidget(mainSubtitle, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(upload_button, 0, Qt::AlignHCenter);
    layout->addWidget(camera_button, 0, Qt::AlignHCenter);
    layout->addWidget(upload_error, 0, Qt::AlignHCenter);

    centralWidget->setLayout(layout);

    // fonts
    QFont maintitleFont("Helvetica", 50, QFont::Bold);
    mainTitle->setFont(maintitleFont);

    QFont mainsubtitleFont("Helvetica", 20, QFont::Medium);
    mainSubtitle->setFont(mainsubtitleFont);

    QFont uploadbuttonFont("Helvetica", 16, QFont::Light);
    upload_button->setFont(uploadbuttonFont);

    QFont camerabuttonFont("Helvetica", 16, QFont::Light);
    camera_button->setFont(camerabuttonFont);

    QFont uploaderrorFont("Helvetica", 14, QFont::StyleItalic);
    upload_error->setFont(uploaderrorFont);

    // Connect
    connect(upload_button, &QPushButton::released, this, &MainWindow::handleUploadButton);
    connect(camera_button, &QPushButton::released, this, &MainWindow::handleCameraButton);
}

void MainWindow::handleUploadButton() {
    QString filePath = QFileDialog::getOpenFileName(this,
        "Select a File",
        "",
        "Images (*.png *.jpg *.jpeg);;Videos (*.mp4 *.mov *.avi);;Documents (*.pdf *.doc *.docx *.txt);;All Files (*.*)");

    if (filePath.isEmpty()) {
        upload_error->setText("No file selected.");
        return;
    } else {
        upload_error->setText("Selected File: " + filePath);

        previewWindow = new previewwindow();
        //add preview window constructor to send file over
        qDebug() << "Filepath:" << previewWindow->property("filepath").toString();

        previewWindow->showMaximized();
        this->close();
    }
}

void MainWindow::handleCameraButton() {
    cameraWindow = new CameraWindow(this);
    cameraWindow->showMaximized();
}

void MainWindow::handleProfileButton() {
    QString username = this->property("username").toString();

    profileWindow = new profilewindow(&username, this);
    profileWindow->showMaximized();
}

void MainWindow::handleSignInButton() {
    loginWindow = new loginwindow(this);
    loginWindow->showMaximized();
}




