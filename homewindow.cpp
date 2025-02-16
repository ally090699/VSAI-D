#include "homewindow.h"

homewindow::homewindow(QWidget *parent) : QMainWindow{parent}{
    homewindow::setWindowTitle("Visual Study AI-D");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);  // Set the central widget for the main window

    mainTitle = new QLabel("Welcome to the Visual Study AI-D!", this);
    //mainSubtitle = new QLabel("", this);

    signin_button = new QPushButton("SIGN IN", this);
    signin_button->setFixedSize(300, 50);
    getstarted_button = new QPushButton("GET STARTED", this);
    getstarted_button->setFixedSize(300, 50);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(mainTitle, 0, Qt::AlignHCenter);
    //layout->addWidget(mainSubtitle, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(signin_button, 0, Qt::AlignHCenter);
    layout->addWidget(getstarted_button, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));

    centralWidget->setLayout(layout);

    //add fonts
    QFont maintitleFont("Helvetica", 50, QFont::Bold);
    mainTitle->setFont(maintitleFont);

    //QFont mainsubtitleFont("Helvetica", 20, QFont::Weight(300));
    //mainSubtitle->setFont(mainsubtitleFont);

    QFont signinFont("Helvetica", 16, QFont::Bold);
    signin_button->setFont(signinFont);

    QFont getstartedFont("Helvetica", 16, QFont::Bold);
    getstarted_button->setFont(getstartedFont);

    connect(signin_button, &QPushButton::released, this, &homewindow::handleSignInButton);
    connect(getstarted_button, &QPushButton::released, this, &homewindow::handleGetStartedButton);

}

void homewindow::handleSignInButton()
{
    loginWindow = new loginwindow();
    loginWindow->showMaximized();
    this->close();
}

void homewindow::handleGetStartedButton()
{
    mainWindow = new MainWindow();
    mainWindow->showMaximized();
    this->close();
}
