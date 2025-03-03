#include "user.h"

user::user(QString username, QString password, QString firstname, QString lastname, QString email) {
    this->userName = username;
    this->passWord = password;
    this->firstName = firstname;
    this->lastName = lastname;
    this->eMail = email;
}

void user::updateEmail(QString newEmail){
    this->eMail = newEmail;
}

void user::updatePassword(QString newPassword){
    this->passWord = newPassword;
}

QString user::getUsername(){
    return this->userName;
}
