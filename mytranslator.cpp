#include <QObject>
#include "mytranslator.h"
#include "mainwindow.h"

#include <iostream>
#include <string>
using namespace std;

MyTranslator::MyTranslator() { }
MyTranslator::MyTranslator(QString word)
{
    proc = nullptr;
    setWord(word);

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
    QString str_command = "ls /";
    mainWin->formWindow->dataEdit->clear();

    proc= new QProcess();
    proc->start("/bin/bash", QStringList() << "-c" << QString(str_command));

    connect(proc, &QProcess::readyReadStandardOutput, this, &MyTranslator::rightMessage );
    connect(proc, &QProcess::readyReadStandardError , this, &MyTranslator::wrongMessage );
}

void MyTranslator::rightMessage()
{
    std::cout << "outputer:\n";
    QString out = mainWin->formWindow->dataEdit->document()->toPlainText();
    QByteArray strdata = proc->readAllStandardOutput();

    std::cout << strdata.constData() << " ok\n";

    mainWin->formWindow->dataEdit->document()->setPlainText(
    QString("%1\n%2").arg(out).arg(strdata.constData()));
}

void MyTranslator::wrongMessage()
{
    QString out = mainWin->formWindow->dataEdit->document()->toPlainText();
    QByteArray strdata = proc->readAllStandardError();

    std::cout << strdata.constData() << " err";

    mainWin->formWindow->dataEdit->document()->setPlainText(
    QString("%1\n%2").arg(out).arg(strdata.constData()));
}
