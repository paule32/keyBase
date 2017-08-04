#include "mainwindow.h"
#include "myformdesigner.h"
#include "mydesignercomponents.h"
#include "haupt.h"

MyFormDesigner::MyFormDesigner(QWidget *parent)
    : QScrollArea(parent)
{
    setGeometry(0,0,200,200);

    MyDesignerComponents *c = new
    MyDesignerComponents(mainWin->ui->formWindow->ui->listWidget_3);

    c->show();

    mainWin->ui->formWindow->ui->editorGutter->setVisible(false);
    mainWin->ui->formWindow->ui->editLayout->replaceWidget(
    mainWin->ui->formWindow->ui->editorGutter,this);

    setEnabled(true);
    show();
}
