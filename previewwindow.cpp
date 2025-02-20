#include "previewwindow.h"
#include "mainwindow.h"

previewwindow::previewwindow(QWidget *parent) : QMainWindow{parent}{
    setupUI();
}

previewwindow::previewwindow(QString username, QWidget *parent) : QMainWindow{parent}{
    this->setProperty("username",username);
}

void previewwindow::setupUI(){
    previewwindow::setWindowTitle("Preview Pane");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);  // Set the central widget for the main window

    mainTitle = new QLabel("Preview", this);
    mainSubtitle = new QLabel("Review your submitted file before proceeding. Click \"Restart\" to upload a new file.", this);

    restartButton = new QPushButton("RESTART", this);
    restartButton->setFixedSize(300, 50);
    continueButton = new QPushButton("CONTINUE", this);
    continueButton->setFixedSize(300, 50);
    QString filepath = this->property("filepath").toString();
    qDebug() <<"Filepath:" << filepath;
    preview_error = new QLabel("Selected File: "+filepath, this);

    QVBoxLayout* layout = new QVBoxLayout();

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

    QFont restartFont("Helvetica", 16, QFont::Light);
    restartButton->setFont(restartFont);

    QFont continueFont("Helvetica", 16, QFont::Light);
    continueButton->setFont(continueFont);

    QFont previewerrorFont("Helvetica", 14, QFont::StyleItalic);
    preview_error->setFont(previewerrorFont);

    connect(restartButton, &QPushButton::released, this, &previewwindow::handleRestartButton);
    connect(continueButton, &QPushButton::released, this, &previewwindow::handleContinueButton);
}

void previewwindow::handleRestartButton()
{
    mainWindow = new MainWindow();
    mainWindow->showMaximized();
    this->close();
}

void previewwindow::handleContinueButton()
{
    videoWindow = new VideoWindow(this->property("username").toString(), this);
    videoWindow->showMaximized();
    this->close();
}
