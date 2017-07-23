#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

#include <QProcess>
#include <QMessageBox>

#include "mainwindow.h"
#include "shapedetector.h"

ShapeDetector::ShapeDetector(QObject *parent) : QObject(parent)
{
    proc = nullptr;
}

ShapeDetector::~ShapeDetector() {
    delete proc;
}

void ShapeDetector::setup(cv::String fname)
{
    QString str_command =
    QString("./detect_shapes.py -i \"%1\"").arg(fname.c_str());

    QMessageBox::information(0,"Info",str_command);

    proc= new QProcess();
    proc->start("/bin/bash", QStringList() << "-c" << QString(str_command));

    connect(proc, &QProcess::readyReadStandardOutput, this, &ShapeDetector::rightMessage );
    connect(proc, &QProcess::readyReadStandardError , this, &ShapeDetector::wrongMessage );
}

void ShapeDetector::rightMessage()
{
    QByteArray strdata = proc->readAllStandardOutput();
    mainWin->ui->formWindow->ui->dataEdit->setPlainText(
    QString("%1").arg(strdata.constData()));
}

void ShapeDetector::wrongMessage()
{
    QByteArray strdata = proc->readAllStandardError();
    mainWin->ui->formWindow->ui->dataEdit->setPlainText(
    QString("%1").arg(strdata.constData()));
}
