#include "databasemanager.h"
#include <QDebug>

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("vsaid.db");
}

DatabaseManager::~DatabaseManager(){
    if (db.isOpen()){
        db.close();
    }
}

DatabaseManager& DatabaseManager::getInstance(){
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connectToDB(){
    if (!db.open()){
        qDebug()<<"Could not connect to database."<<db.lastError().text();
        return false;
    }
    qDebug()<<"Successfully connected to database!";
    return true;
}

bool DatabaseManager::createTables(){
    QSqlQuery query;
    bool success = query.exec(
        "CREATE TABLE IF NOT EXISTS users ("
        "userid INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT,"
        "password TEXT,"
        "firstname TEXT,"
        "lastname TEXT,"
        "email TEXT)"
        );
    success &= query.exec(
        "CREATE TABLE IF NOT EXISTS favourites ("
        "uploadId INTEGER PRIMARY KEY AUTOINCREMENT, "
        "uploadPath TEXT, "
        "outputPath TEXT, "
        "userid INTEGER, "
        "FOREIGN KEY(userid) REFERENCES users(userid))"
        );

    if (!success) {
        qDebug() << "Error creating tables:" << query.lastError().text();
    }

    return success;
}

bool DatabaseManager::addUser(const QString& username, const QString& password, const QString& firstname, const QString& lastname, const QString& email){
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, firstname, lastname, email) VALUES (:username, :password, :firstname, :lastname, :email)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":firstname", firstname);
    query.bindValue(":lastname", lastname);
    query.bindValue(":email", email);
    return query.exec();
}

user DatabaseManager::getUser(const QString& userID) {
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE userid = :userid");
    query.bindValue(":userid", userID);

    if (query.exec() && query.next()) {
        return user(userID, query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString());
    }

    return user("", "", "", "", "");
}

bool DatabaseManager::addFavourite(const QString& uploadPath, const QString& outputPath, const QString& userID) {
    QSqlQuery query;
    query.prepare("INSERT INTO favourites (uploadPath, outputPath, userid) VALUES (:uploadpath, :outputpath, :userid)");
    query.bindValue(":uploadPath", uploadPath);
    query.bindValue(":outputPath", outputPath);
    query.bindValue(":userid", userID);
    return query.exec();
}

QList<std::tuple<QString, QString, int>> DatabaseManager::getFavourites(const int userID) {
    QList<std::tuple<QString, QString, int>> favourites;
    QSqlQuery query;
    query.prepare("SELECT uploadPath, outputPath, userid FROM favourites WHERE userid = :userId");
    query.bindValue(":userId", userID);

    if (query.exec()) {
        while (query.next()) {
            favourites.append(std::make_tuple(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt()));
        }
    }

    return favourites;
}
