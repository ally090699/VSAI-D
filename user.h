#ifndef USER_H
#define USER_H

#include <QString>

class user
{
public:
    explicit user(QString username, QString password, QString firstname, QString lastname, QString email);
    QString getUsername();
    QString getFirstName();
    QString getLastName();
    QString getEmail();
protected:
    void updateEmail(QString newEmail);
    void updatePassword(QString newPassword);

private:
    QString userName;
    QString passWord;
    QString firstName;
    QString lastName;
    QString eMail;
};

#endif // USER_H
