#include "homewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    homewindow homeWindow;
    homeWindow.setWindowTitle("Visual Study AI-D");
    homeWindow.showMaximized();
    return app.exec();
}
