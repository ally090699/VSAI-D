#include "user.h"

user::user(QString username, QString password, QString firstname, QString lastname, QString email) {
    this->userName = username;
    this->passWord = password;
    this->firstName = firstname;
    this->lastName = lastname;
    this->eMail = email;
    this->favourites = new QVariantMap;
}

QVariantMap user::loadFavourites(){
    return *favourites;
}

bool user::insertFavourite(int uploadID, QString uploadPath, QString outputPath){

}

void user::updateEmail(QString newEmail){

}

void user::updatePassword(QString newPassword){

}
