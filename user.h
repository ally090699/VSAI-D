#ifndef USER_H
#define USER_H

#include <QString>
#include <QVariantMap>

class user
{
public:
    explicit  user(QString username, QString password, QString firstname, QString lastname, QString email);
    QString getUsername();
    QString getFirstName();
    QString getLastName();
    QString getEmail();
protected:
    QVariantMap loadFavourites();
    bool insertFavourite(int uploadID, QString uploadPath, QString outputPath);
    void updateEmail(QString newEmail);
    void updatePassword(QString newPassword);

private:
    QString userName;
    QString passWord;
    QString firstName;
    QString lastName;
    QString eMail;
    QVariantMap *favourites;

};

#endif // USER_H
