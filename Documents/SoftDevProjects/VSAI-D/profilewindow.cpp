#include "profilewindow.h"

profilewindow::profilewindow(QWidget *parent) : QMainWindow{parent}{
    profilewindow::setWindowTitle("Visual Study AI-D");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);  // Set the central widget for the main window

    mainTitle = new QLabel("Profile", this);
    //add vbox with list of previously uploaded content
    favouriteButton = new QPushButton("♥️", this);
    favouriteButton->setFixedSize(300, 50);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(mainTitle, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(favouriteButton, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));

    centralWidget->setLayout(layout);

    //add fonts
    QFont maintitleFont("Helvetica", 30, QFont::Bold);
    mainTitle->setFont(maintitleFont);

    QFont favouriteFont("Helvetica", 16, QFont::Weight(300));
    favouriteButton->setFont(favouriteFont);

    connect(favouriteButton, &QPushButton::released, this, &profilewindow::handleFavouriteButton);

}

void profilewindow::handleFavouriteButton()
{

}
