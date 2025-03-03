#ifndef VIDEOWINDOW_H
#define VIDEOWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QPushButton>

#include "profilewindow.h"

class VideoWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit VideoWindow(QWidget *parent = nullptr);
    VideoWindow(QString username, QWidget *parent = nullptr);
    QWidget* previousWindow;
private slots:
    void setupUI();
    void handleProfileButton();
    void handleReturn();
private:
    QVBoxLayout *layout;
    QVideoWidget *videoWidget;
    QPushButton *profile_button;
    QPushButton *return_button;
    profilewindow *profileWindow;
    QPushButton *uploadagain_button;
signals:
};

#endif // VIDEOWINDOW_H
