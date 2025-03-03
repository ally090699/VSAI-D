#include "profilewindow.h"
#include "databasemanager.h"

profilewindow::profilewindow(QString *username, QWidget *parent) : QMainWindow{parent}{
    userName = username;
    setupUI();
}

void profilewindow::setupUI(){
    profilewindow::setWindowTitle("Profile");

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);  // Set the central widget for the main window
    QString title = userName->append("'s Profile");
    mainTitle = new QLabel(title, this);
    //add vbox with list of previously uploaded content
    DatabaseManager& dbManager = DatabaseManager::getInstance();

    if (dbManager.connectToDB()){
        int retrievedUserId = dbManager.getUserId(*this->userName);

        if (retrievedUserId==0){
            qDebug()<<"User not found.";
        } else{
            qDebug()<<"User ID: "<<retrievedUserId;
        }

        user retrievedUser = dbManager.getUser(retrievedUserId);

        usernameInput = new QLineEdit();
        usernameInput->setPlaceholderText(retrievedUser.getUsername());

    }
    favouriteButton = new QPushButton("♥️", this);
    favouriteButton->setFixedSize(300, 50);

    return_button = new QPushButton("←", this);
    return_button->setFixedSize(300, 50);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addWidget(return_button, 0, Qt::AlignLeft);
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

    QFont returnbuttonFont("Helvetica", 16, QFont::Medium);
    return_button->setFont(returnbuttonFont);

    connect(favouriteButton, &QPushButton::released, this, &profilewindow::handleFavouriteButton);
    connect(return_button, &QPushButton::released, this, &profilewindow::handleReturn);
}

void profilewindow::handleFavouriteButton()
{

}

void profilewindow::handleReturn(){
    if (previousWindow) {
        previousWindow->show();
        this->close();
    }
}
