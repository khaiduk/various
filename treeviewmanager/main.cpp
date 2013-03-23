#include <QtGui/QApplication>
#include "mainwindow.h"
#include "filesystemcontroller.h"
#include "ulubioneaction.h"
int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
