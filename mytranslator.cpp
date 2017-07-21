#include <QObject>
#include "mytranslator.h"
#include "mainwindow.h"

#include <iostream>
#include <string>
using namespace std;

MyTranslator::MyTranslator(QString &w)
{
    proc = nullptr;
    word = w;

    if (source.length() < 1) setSource("DE");
    if (target.length() < 1) setTarget("EN");
}

MyTranslator::~MyTranslator() {
    delete proc;
}

void MyTranslator::setWord(QString w) {
    word = w;
}

void MyTranslator::setSource(QString s) { source = s; }
void MyTranslator::setTarget(QString s) { source = s; }

void MyTranslator::translate()
{
    std::cout << "--> " << word.toStdString() << std::endl;
    QString str_command =
    QString("./trans -b -s en -t de -play \"%1\"").arg(word);
    mainWin->ui->formWindow->ui->dataEdit->clear();

    proc= new QProcess();
    proc->start("/bin/bash", QStringList() << "-c" << QString(str_command));

    connect(proc, &QProcess::readyReadStandardOutput, this, &MyTranslator::rightMessage );
    connect(proc, &QProcess::readyReadStandardError , this, &MyTranslator::wrongMessage );
}

void MyTranslator::rightMessage()
{
    QByteArray strdata = proc->readAllStandardOutput();
    mainWin->ui->formWindow->ui->dataEdit->setPlainText(
    QString("%1").arg(strdata.constData()));
}

void MyTranslator::wrongMessage()
{
    QByteArray strdata = proc->readAllStandardError();
    mainWin->ui->formWindow->ui->dataEdit->setPlainText(
    QString("%1").arg(strdata.constData()));
}
