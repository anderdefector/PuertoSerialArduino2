#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(434,122);
    w.setWindowTitle("Prueba 2");
    w.show();

    return a.exec();
}
