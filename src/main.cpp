#include "header/mainwindow.h"
#include "header/questdialog.h"
#include "header/autobot.h"
#include <thread>
#include <windows.h>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
