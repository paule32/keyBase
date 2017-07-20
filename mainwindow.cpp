#include "ui_haupt.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    formWindow = new Ui::Form;
    formWindow->setupUi(this);

    ui = new Ui::MainWindow;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
