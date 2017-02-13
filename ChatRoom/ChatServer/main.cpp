//#include "headers/forms/mainwindow.h"
#include <QApplication>
#include <headers/forms/mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   w.show();

    return a.exec();
}
