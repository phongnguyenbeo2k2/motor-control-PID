#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    /*set size of app is full screen*/
    w.setWindowState(Qt::WindowMaximized);
    w.show();
    w.setWindowIcon(QIcon(":/resource/image/motor.png"));
//    w.setStyleSheet("color: rgb(244, 244, 244);");
    return a.exec();
}
