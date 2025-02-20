#include "videowindow.h"

VideoWindow::VideoWindow(QWidget *parent) : QMainWindow{parent}{
    setupUI();
}

VideoWindow::VideoWindow(QString username, QWidget *parent) : QMainWindow{parent}{
    this->setProperty("username", username);
    if (!username.isEmpty()) {
        qDebug()<<"User "<<this->property("username").toString()<<" has logged in--> Video Window";
        profile_button = new QPushButton("Profile", this);
        profile_button->setFixedSize(300, 50);

        layout->addWidget(profile_button, 0, Qt::AlignHCenter);
        layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));

        connect(profile_button, &QPushButton::released, this, &VideoWindow::handleProfileButton);
    }
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
    layout->addWidget(videoWidget);
    layout->addWidget(uploadagain_button, 0, Qt::AlignHCenter);
}

void VideoWindow::handleProfileButton(){
    QString username = this->property("username").toString();
    profileWindow = new profilewindow(&username, this);
    profileWindow->showMaximized();
}
