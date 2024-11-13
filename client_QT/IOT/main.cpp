#include "./mainwindow/mainwindow.h"
#include "./client_simple/client_simple.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
