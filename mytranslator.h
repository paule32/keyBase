#ifndef MYTRANSLATOR_H
#define MYTRANSLATOR_H

#include <QObject>
#include <QString>
#include <QProcess>

class MyTranslator: public QObject
{
public:
     explicit MyTranslator(QString&w);
    ~MyTranslator();

    void translate();

public slots:
    void rightMessage();
    void wrongMessage();

public:
    void setSource(QString);
    void setTarget(QString);
    void setWord(QString);

    QString source;
    QString target;
    QString word;

    QProcess *proc;
};

#endif // MYTRANSLATOR_H
