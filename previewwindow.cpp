#include "previewwindow.h"
#include "mainwindow.h"

previewwindow::previewwindow(QWidget *parent) : QMainWindow{parent}{
    setupUI();
}

previewwindow::previewwindow(QString username, QString filepath, QWidget *parent) : QMainWindow{parent}{
    this->setProperty("username",username);
    this->setProperty("filepath",filepath);
    setupUI();
}

void previewwindow::setupUI(){
    previewwindow::setWindowTitle("Preview Pane");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainTitle = new QLabel("Preview", this);
    mainSubtitle = new QLabel("Review your submitted file before proceeding. Click \"Restart\" to upload a new file.", this);

    restartButton = new QPushButton("RESTART", this);
    restartButton->setFixedSize(300, 50);

    continueButton = new QPushButton("CONTINUE", this);
    continueButton->setFixedSize(300, 50);

    return_button = new QPushButton("←", this);
    return_button->setFixedSize(300, 50);

    QString filepath = this->property("filepath").toString();
    qDebug() <<"Filepath:" << filepath;
    preview_error = new QLabel("Selected File: "+filepath, this);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(return_button, 0, Qt::AlignLeft);
    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(mainTitle, 0, Qt::AlignHCenter);
    layout->addWidget(mainSubtitle, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(restartButton, 0, Qt::AlignHCenter);
    layout->addWidget(continueButton, 0, Qt::AlignHCenter);
    layout->addWidget(preview_error, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));

    centralWidget->setLayout(layout);

    //add fonts
    QFont maintitleFont("Helvetica", 30, QFont::Bold);
    mainTitle->setFont(maintitleFont);

    QFont mainsubtitleFont("Helvetica", 20, QFont::Medium);
    mainSubtitle->setFont(mainsubtitleFont);

    QFont buttonFont("Helvetica", 16, QFont::Light);
    restartButton->setFont(buttonFont);
    continueButton->setFont(buttonFont);

    QFont previewerrorFont("Helvetica", 14, QFont::StyleItalic);
    preview_error->setFont(previewerrorFont);

    QFont returnbuttonFont("Helvetica", 16, QFont::Medium);
    return_button->setFont(returnbuttonFont);

    connect(restartButton, &QPushButton::released, this, &previewwindow::handleRestartButton);
    connect(continueButton, &QPushButton::released, this, &previewwindow::handleContinueButton);
    connect(return_button, &QPushButton::released, this, &previewwindow::handleReturn);
}

void previewwindow::handleRestartButton()
{
    if (!this->property("username").isNull()){
        mainWindow = new MainWindow(this->property("username").toString(), this);
    } else {
        mainWindow = new MainWindow(this);
    }
    mainWindow = new MainWindow();
    mainWindow->previousWindow = this;
    mainWindow->showMaximized();
    this->hide();
}

void previewwindow::handleContinueButton()
{
    if (!this->property("username").isNull()){
        videoWindow = new VideoWindow(this->property("username").toString(), this);
    } else {
        videoWindow = new VideoWindow(this);
    }
    videoWindow = new VideoWindow(this->property("username").toString(), this);
    videoWindow->previousWindow = this;
    videoWindow->showMaximized();
    this->hide();
}

void previewwindow::handleReturn(){
    if (previousWindow) {
        previousWindow->show();
        this->close();
    }
}
