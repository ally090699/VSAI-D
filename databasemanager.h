#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QList>
#include <tuple>

#include "user.h"

class DatabaseManager
{
public:
    static DatabaseManager& getInstance();
    bool connectToDB();
    bool createTables();
    bool addUser(const QString& username, const QString& password, const QString& firstname, const QString& lastname, const QString& email);
    user getUser(const int userid);
    int getUserId(const QString& username);
    bool addFavourite(const QString& uploadPath, const QString& outputPath, const QString& username);
    QList<std::tuple<QString, QString, int>> getFavourites(const int userID);
private:
    DatabaseManager();
    ~DatabaseManager();
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
