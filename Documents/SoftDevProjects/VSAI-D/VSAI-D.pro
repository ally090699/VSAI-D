QT       += core gui widgets multimedia multimediawidgets sql
CONFIG += permissions;
TARGET = VSAID
TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp \
    camerawindow.mm \
    homewindow.cpp \
    loginwindow.cpp \
    previewwindow.cpp \
    profilewindow.cpp
HEADERS += mainwindow.h camerawindow.h \
    homewindow.h \
    loginwindow.h \
    previewwindow.h \
    profilewindow.h

RESOURCES += resources.qrc

macx:QMAKE_INFO_PLIST = $$PWD/Info.plist
macx:LIBS += -framework AVFoundation
QMAKE_MACOSX_DEPLOYMENT_TARGET = 12.0
QMAKE_ENTITLEMENTS = $$PWD/Entitlements.plist

macx {
    QMAKE_POST_LINK += cp $$PWD/Info.plist $$OUT_PWD/VSAID.app/Contents/Info.plist;
    QMAKE_POST_LINK += codesign --deep --force --verbose --entitlements $$PWD/Entitlements.plist --sign "Developer ID Application: ally090699@hotmail.com (4NFL89X5LY)" $$OUT_PWD/VSAID.app;
}




