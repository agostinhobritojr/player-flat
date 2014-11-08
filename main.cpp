#include "mainwindow.h"
#include <QApplication>

// you should not touch here ;)
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
