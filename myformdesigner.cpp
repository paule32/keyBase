#include "mainwindow.h"
#include "myformdesigner.h"
#include "mydesignercomponents.h"
#include "mydesignergraphicsview.h"

#include "haupt.h"

MyFormDesigner::MyFormDesigner(QWidget *parent)
    : QScrollArea(parent)
{
    setGeometry(0,0,200,200);
    setStyleSheet("background-color: white;");

    MyDesignerComponents *c = new
    MyDesignerComponents(mainWin->ui->formWindow->ui->listWidget_3);

    c->show();

    MyDesignerGraphicsView *v = new
    MyDesignerGraphicsView(this);

    mainWin->ui->formWindow->ui->editorGutter->hide();
    mainWin->ui->formWindow->ui->editorGutter->setEnabled(false);
    mainWin->ui->formWindow->ui->editLayout->addWidget(this);
}
