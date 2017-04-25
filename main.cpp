#include "mainwindow.h"
#include "output.h"
#include <QApplication>

int main(int argc, char *argv[])
{
       Output b;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}
