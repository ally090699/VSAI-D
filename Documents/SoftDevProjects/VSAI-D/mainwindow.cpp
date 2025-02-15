#include "mainwindow.h"
#include "previewwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    MainWindow::setWindowTitle("Visual Study AI-D");
    //main window layout
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);  // Set the central widget for the main window
    mainTitle = new QLabel("Welcome to the Visual Study AI-D!", this);
    mainSubtitle = new QLabel("To get started, upload a file containing your video or notes to generate an animated summary.", this);
    upload_button = new QPushButton("Upload File (.mp4, .pdf, .docx, etc.)", this);
    upload_button->setFixedSize(600, 100);
    upload_error = new QLabel("", this);
    //preview_button = new QPushButton("Upload File (.mp4, .pdf, .docx, etc.)", this);
    camera_button = new QPushButton("Use Camera", this);
    camera_button->setFixedSize(300, 50);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(mainTitle, 0, Qt::AlignHCenter);
    layout->addWidget(mainSubtitle, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(upload_button, 0, Qt::AlignHCenter);
    layout->addWidget(camera_button, 0, Qt::AlignHCenter);
    layout->addWidget(upload_error, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));

    centralWidget->setLayout(layout);

    //add fonts
    QFont maintitleFont("Helvetica", 50, QFont::Bold);
    mainTitle->setFont(maintitleFont);

    QFont mainsubtitleFont("Helvetica", 20, QFont::Weight(300));
    mainSubtitle->setFont(mainsubtitleFont);

    QFont uploadbuttonFont("Helvetica", 16, QFont::Weight(300));
    upload_button->setFont(uploadbuttonFont);

    QFont camerabuttonFont("Helvetica", 16, QFont::Weight(300));
    camera_button->setFont(camerabuttonFont);

    QFont uploaderrorFont("Helvetica", 14, QFont::StyleItalic);
    upload_error->setFont(uploaderrorFont);

    connect(upload_button, &QPushButton::released, this, &MainWindow::handleUploadButton);
    connect(camera_button, &QPushButton::released, this, &MainWindow::handleCameraButton);

}

void MainWindow::handleUploadButton()
{
    QString filePath = QFileDialog::getOpenFileName(this,
        "Select a File",
        "",
        "Images (*.png *.jpg *.jpeg);;Videos (*.mp4 *.mov *.avi);;Documents (*.pdf *.doc *.docx *.txt);;All Files (*.*)");

    if (filePath.isEmpty()) {
        upload_error->setText("No file selected.");
        return;
    } else {
        upload_error->setText(QString::fromStdString("Selected File: " + filePath.toStdString()));
        previewWindow = new previewwindow();
        previewWindow->setProperty("filepath", filePath);
        QString test = previewWindow->property("filepath").toString();
        qDebug() <<"Filepath:" << test;
        previewWindow->showMaximized();
        this->close();
    }
}

void MainWindow::handleCameraButton()
{   // opens Camera Window
    cameraWindow = new CameraWindow(this); // Create CameraWindow instance
    cameraWindow->show();
}




