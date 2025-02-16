#ifndef PREVIEWWINDOW_H
#define PREVIEWWINDOW_H

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

#include "profilewindow.h"
class MainWindow;

class previewwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit previewwindow(QWidget *parent = nullptr);
private slots:
    void handleRestartButton();
    void handleContinueButton();
private:
    QVBoxLayout *layout;
    QLabel *mainTitle;
    QLabel *mainSubtitle;
    QPushButton *restartButton;
    QPushButton *continueButton;
    QLabel *preview_error;
    MainWindow *mainWindow;
    profilewindow *profileWindow;
};
#endif // MAINWINDOW_H
