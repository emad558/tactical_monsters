#include <QApplication>
#include "splash.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SplashScreen splash;
    MainWindow mainWin;

    QObject::connect(&splash, &SplashScreen::startClicked, [&]() {
        splash.hide();
        mainWin.show();
    });

    splash.show();
    return app.exec();
}
