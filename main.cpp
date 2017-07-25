#include "mainwindow.h"
#include <QApplication>

#include <Qt3DCore/Qt3DCore>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

using namespace Qt3DExtras;

#include "dreidworld.h"

Qt3DExtras::Qt3DWindow *view = nullptr;
MainWindow *mainWin          = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    view = new Qt3DWindow;

    mainWin = new MainWindow;
    mainWin->show();

    return a.exec();
}
