QT       += core gui widgets multimedia multimediawidgets sql
CONFIG += permissions;
TARGET = VSAID
TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp \
    camerawindow.cpp \
    computervision.cpp \
    databasemanager.cpp \
    homewindow.cpp \
    loginwindow.cpp \
    previewwindow.cpp \
    profilewindow.cpp \
    user.cpp \
    videowindow.cpp
HEADERS += mainwindow.h \
    camerawindow.h \
    computervision.h \
    databasemanager.h \
    homewindow.h \
    loginwindow.h \
    previewwindow.h \
    profilewindow.h \
    user.h \
    videowindow.h

RESOURCES += resources.qrc

INCLUDEPATH += /usr/local/Cellar/opencv/4.11.0_1/include/opencv4
INCLUDEPATH += /usr/local/Cellar/tesseract/5.5.0/include
LIBS += -L/usr/local/Cellar/opencv/4.11.0_1/lib -lopencv_core -lopencv_imgproc -lopencv_videoio -lopencv_highgui -lopencv_imgcodecs
LIBS += -L/usr/local/Cellar/tesseract/5.5.0/lib -ltesseract

INCLUDEPATH += /usr/local/Cellar/ffmpeg/7.1_4/include
LIBS += -L/usr/local/Cellar/ffmpeg/7.1_4/lib \
        -lavformat -lavcodec -lavutil -lswscale
