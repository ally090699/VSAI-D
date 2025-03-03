#include "videowindow.h"

VideoWindow::VideoWindow(QWidget *parent) : QMainWindow{parent}{
    setupUI();
}

VideoWindow::VideoWindow(QString username, QWidget *parent) : QMainWindow{parent}{
    this->setProperty("username", username);
    setupUI();
}

void VideoWindow::setupUI(){
    setWindowTitle("Video Summary");

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    uploadagain_button = new QPushButton("Upload a New File", this);
    uploadagain_button->setFixedSize(300, 50);

    videoWidget = new QVideoWidget(this);

    return_button = new QPushButton("←", this);
    return_button->setFixedSize(300, 50);

    layout->addWidget(return_button, 0, Qt::AlignLeft);
    layout->addWidget(videoWidget);
    layout->addWidget(uploadagain_button, 0, Qt::AlignHCenter);

    QFont returnbuttonFont("Helvetica", 16, QFont::Medium);
    return_button->setFont(returnbuttonFont);

    connect(return_button, &QPushButton::released, this, &VideoWindow::handleReturn);

    QString username = this->property("username").toString();

    if (!username.isEmpty()) {
        qDebug()<<"User "<<this->property("username").toString()<<" has logged in--> Video Window";
        profile_button = new QPushButton("Profile", this);
        profile_button->setFixedSize(300, 50);

        layout->addWidget(profile_button, 0, Qt::AlignHCenter);

        connect(profile_button, &QPushButton::released, this, &VideoWindow::handleProfileButton);
    }
}

void VideoWindow::handleProfileButton(){
    QString username = this->property("username").toString();
    profileWindow = new profilewindow(&username, this);
    profileWindow->previousWindow = this;
    profileWindow->showMaximized();
    this->hide();
}

void VideoWindow::handleReturn(){
    if (previousWindow) {
        previousWindow->show();
        this->close();
    }
}
