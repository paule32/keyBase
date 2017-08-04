#ifndef MYEDITCOMPLETER_H
#define MYEDITCOMPLETER_H

#include <QTextEdit>
#include "editorgutter.h"

class QCompleter;

class MyEditCompleter : public MyEditor
{
    Q_OBJECT
public:
    MyEditCompleter(QWidget *parent = 0);
    ~MyEditCompleter();

    void setCompleter(QCompleter *c);
    QCompleter *completer() const;

protected:
    void keyPressEvent(QKeyEvent  *e);
    void focusInEvent(QFocusEvent *e);
    void resizeEvent(QResizeEvent *e);

private slots:
    void insertCompletion(const QString &completion);

private:
    QString textUnderCursor() const;
private:
    QCompleter *c;
};

#endif // MYEDITCOMPLETER_H
