#ifndef MYTRANSLATOR_H
#define MYTRANSLATOR_H

#include <QObject>
#include <QString>
#include <QProcess>

class MyTranslator: public QObject
{
public:
     explicit MyTranslator();
     explicit MyTranslator(QString);
    ~MyTranslator();

    void translate();

public slots:
    void rightMessage();
    void wrongMessage();

public:
    void setSource(QString);
    void setTarget(QString);
    void setWord(QString);

    mutable QString source;
    mutable QString target;

    mutable QString word;

    QProcess *proc;
};

#endif // MYTRANSLATOR_H
