#ifndef PROFILEWINDOW_H
#define PROFILEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFont>
#include <QGuiApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class profilewindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit profilewindow(QString *username, QWidget *parent = nullptr);
private slots:
    void handleFavouriteButton();
    void setupUI();
private:
    QString *userName;
    QVBoxLayout *layout;
    QLabel *mainTitle;
    QLabel *mainSubtitle;
    QVBoxLayout *pastUploads;
    QPushButton *favouriteButton;
};
#endif // PROFILEWINDOW_H
