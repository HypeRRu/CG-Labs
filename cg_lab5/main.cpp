#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Максименко Егор КГ Лаб. 5");
    a.setAttribute(Qt::AA_UseDesktopOpenGL);
    return a.exec();
}
