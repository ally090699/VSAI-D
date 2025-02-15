#include "loginwindow.h"
#include "mainwindow.h"

loginwindow::loginwindow(QWidget *parent) : QMainWindow{parent}{
    loginwindow::setWindowTitle("Visual Study AI-D");
    connectDatabase();

    //main window layout
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);  // Set the central widget for the main window

    mainTitle = new QLabel("Welcome to the Visual Study AI-D!", this);
    mainSubtitle = new QLabel("To get started, enter a username and password to log in or register.", this);

    usernameInput = new QLineEdit();
    usernameInput->setPlaceholderText("Enter your username");
    usernameInput->resize(300, 50);
    passwordInput = new QLineEdit();
    passwordInput->setPlaceholderText("Enter your password");
    passwordInput->resize(300, 50);

    register_button = new QPushButton("REGISTER", this);
    register_button->setFixedSize(300, 50);
    login_button = new QPushButton("LOGIN", this);
    login_button->setFixedSize(300, 50);
    login_error = new QLabel("", this);

    QVBoxLayout* layout = new QVBoxLayout();

    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(mainTitle, 0, Qt::AlignHCenter);
    layout->addWidget(mainSubtitle, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed));
    layout->addWidget(usernameInput, 0, Qt::AlignHCenter);
    layout->addWidget(passwordInput, 0, Qt::AlignHCenter);
    layout->addWidget(register_button, 0, Qt::AlignHCenter);
    layout->addWidget(login_button, 0, Qt::AlignHCenter);
    layout->addWidget(login_error, 0, Qt::AlignHCenter);
    layout->addItem(new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed));

    centralWidget->setLayout(layout);

    //add fonts
    QFont maintitleFont("Helvetica", 50, QFont::Bold);
    mainTitle->setFont(maintitleFont);

    QFont mainsubtitleFont("Helvetica", 20, QFont::Weight(300));
    mainSubtitle->setFont(mainsubtitleFont);

    QFont registerbuttonFont("Helvetica", 16, QFont::Weight(300));
    register_button->setFont(registerbuttonFont);

    QFont loginbuttonFont("Helvetica", 16, QFont::Weight(300));
    login_button->setFont(loginbuttonFont);

    QFont loginerrorFont("Helvetica", 14, QFont::StyleItalic);
    login_error->setFont(loginerrorFont);

    connect(register_button, &QPushButton::released, this, &loginwindow::handleRegisterButton);
    connect(login_button, &QPushButton::released, this, &loginwindow::handleLoginButton);

}

void loginwindow::handleRegisterButton()
{
    //input into database
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (loginwindow::insertUser(username, password)){
        login_error->setText("User successfully registered!");
        usernameInput->setText("");
        passwordInput->setText("");
    }
}

void loginwindow::handleLoginButton()
{
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if ((username=="admin" && password=="test123") || authenticateUser(username, password)){
        qDebug() <<"Logged in successfully!";
        mainWindow = new MainWindow();
        mainWindow->showMaximized();
        this->close();
    }
    else {
        qDebug() <<"Incorrect login.";
        login_error->setText("Incorrect username or password. Please try again.");
    }
}

void loginwindow::connectDatabase(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    if (!db.open()) {
        qDebug() << "Error: Could not open database!";
        return;
    }
    qDebug() << "Database connected successfully!";

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS user (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT)");
}

bool loginwindow::insertUser(const QString& username, const QString& password){
    QSqlQuery query;

    // Check if username already exists
    query.prepare("SELECT COUNT(*) FROM user WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Error checking username existence:" << query.lastError().text();
        return false;
    }

    // Move to the first result row and check the count
    if (query.next() && query.value(0).toInt() > 0) {
        login_error->setText("An account with this username already exists.");
        qDebug() << "Username already exists!";
        return false;
    }

    // Insert if username is unique
    query.prepare("INSERT INTO user (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    query.bindValue(":password", hashedPassword);

    if (!query.exec()) {
        qDebug() << "Error inserting user:" << query.lastError().text();
        return false;
    }

    qDebug() << "User registered successfully!";
    return true;
}

bool loginwindow::authenticateUser(const QString& username, const QString& password){
    QSqlQuery query;
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    query.prepare("SELECT * FROM user WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", hashedPassword);

    if (query.exec() && query.next()) {
        qDebug() << "Login successful!";
        return true;
    }
    qDebug() << "Invalid username or password.";
    return false;
}
