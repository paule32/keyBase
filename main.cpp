#include "mainwindow.h"
#include <QApplication>

MainWindow *mainWin = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainWin = new MainWindow;
    mainWin->show();

    return a.exec();
}
