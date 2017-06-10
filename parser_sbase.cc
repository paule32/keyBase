#include <stdio.h>

#include <iostream>
#include <vector>

#include <QString>
#include <QVariant>
#include <QMap>
#include <QMessageBox>
#include <QRegExp>

#include <QDebug>

int line_no  = 1;
int file_eof = 0;

const int cmd_invalid    = 0;
const int cmd_assign     = 1;  // var = 12
const int cmd_assign_new = 2;  // var = new ...

// -------------------
// our AST struct ...
// -------------------
struct MyNode {
public:
    int command;
    int counter;
    QString name;
    QVariant value;
    struct MyNode *prev;
};
QMap<QString, MyNode> ptr_node;
struct MyNode prev_node;

QString newnum;
QString number, ident;

int pos = -1; // buffer position
bool in_comment  = false;
bool end_of_file = false;

// proto types ...
int  handle_space(char *buffer);

// -----------------------------------
// inline's for code make-up ...
// -----------------------------------
int if_overchar(char *buffer) {
    int c = 1;
    while (1) {
        if (++pos > strlen(buffer))
        return 0;
        c = buffer[pos];
        if (c == ' ' || c == '\t') {
            continue;
        }
        else if (c == '/') {
            while (1) {
                if (++pos > strlen(buffer))
                return 0;
                c = buffer[pos];
                if (c == '/') {
                    while (1) {
                        if (++pos > strlen(buffer))
                        return 0;
                        c = buffer[pos];
                        if (c == '\n') {
                            ++line_no;
                            return 1;
                        }
                        else if (c == EOF) {
                            file_eof = 1;
                            return 0;
                        }
                    }
                }
                else if (c == '*') {
                    while (1) {
                        if (++pos > strlen(buffer))
                        return 0;
                        c = buffer[pos];
                        if (c == '*') {
                            while (1) {
                                if (++pos > strlen(buffer))
                                return 0;
                                c = buffer[pos];
                                if (c == '/') {
                                    return 1;
                                }
                                else if (c == '\n') {
                                    ++line_no;
                                    continue;
                                }
                                else if (c == EOF) {
                                    file_eof = 1;
                                    return 0;
                                }
                            }
                        }
                    }
                }
                else if (c == ' ' || c == '\t') {
                    while (1) {
                        if (++pos > strlen(buffer))
                        return 0;
                        c = buffer[pos];
                        if (c == ' ' || c == '\t') {
                            continue;
                        }
                        else if (c == '\n') {
                            ++line_no;
                            break;
                        }
                        else if (c == EOF) {
                            file_eof = 1;
                            return 0;
                        }
                        else {
                            return 0;
                        }
                    }
                }
                else if (((c >= 'a') && (c <= 'z'))
                     ||  ((c >= 'A') && (c <= 'Z'))
                     ||   (c == '_')) {
                    ident += c;
                    while (1) {
                        if (++pos > strlen(buffer))
                        return 0;
                        c = buffer[pos];
                        if (c == ' ' || c == '\t') {
                            return 1;
                        }
                        else if (c == '\n') {
                            ++line_no;
                            return 1;
                        }
                        else if (c == '=') { //go3:
                            qDebug() << "=======";
                            while (1) {
                                if (++pos > strlen(buffer))
                                return 0;
                                c = buffer[pos];
                                if (c == ' ' || c == '\t') {
                                    continue;
                                }
                                else if (c == '\n') {
                                    ++line_no;
                                    continue;
                                }
                                else if ((c >= '0') && (c <= '9')) {
                                    number += c;
                                    while (1) {
                                        if (++pos > strlen(buffer))
                                        return 0;
                                        c = buffer[pos];
                                        if ((c >= '0') && (c <= '9')) {
                                            number += c;
                                            continue;
                                        }
                                        else if (c == ' ' || c == '\t') {
                                            continue;
                                        }
                                        else if (c == '\n') {
                                            ++line_no;
                                            continue;
                                        }
                                        else if (c == EOF) {
                                            file_eof = 1;
                                            return 1;
                                        }
                                        else {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        else if (((c >= 'a') && (c <= 'z'))
                             ||  ((c >= 'A') && (c <= 'Z'))
                             ||   (c == '_')) {
                            ident += c;
                            continue;
                        }
                    }
                }
                else if (c == '+' || c == '-' || c == '*') {
                    return c;
                }
                else if (c == '\n') {
                    ++line_no;
                    break;
                }
                else if (c == EOF) {
                    file_eof = 1;
                    return 0;
                }
            }
        }
        else if (c == EOF) {
            file_eof = 1;
            return 1;
        }
        else if (c == '\n') {
            ++line_no;
            continue;
        }
        else if (((c >= 'a') && (c <= 'z'))
             ||  ((c >= 'A') && (c <= 'Z'))
             ||   (c == '_')) {
            ident += c;
            qDebug() << "ident1: " << ident;
            while (1) {
                if (++pos > strlen(buffer))
                return 0;
                c = buffer[pos];
                if (((c >= 'a') && (c <= 'z'))
                ||  ((c >= 'A') && (c <= 'Z'))
                ||   (c == '_')) {
                    ident += c;
                    qDebug() << "ident2: " << ident;
                    continue;
                }
                if (c == ' ' || c == '\t') {
                    qDebug() << "--__--";
                    while (1) {
                        if (++pos > strlen(buffer))
                        return 0;
                        c = buffer[pos];
                        if (c == ' ' || c == '\t') {
                            qDebug() << "T";
                            continue;
                        }
                        else if (c == '\n') {
                            ++line_no;
                            continue;
                        }
                        if (c == EOF) {
                            file_eof = 1;
                            return 1;
                        }
                        else if (c == '=') {
                            break;
                        }
                    }
                }
                if (c == EOF) {
                    file_eof = 1;
                    return 0;
                }
                else if (c == '\n') {
                    ++line_no;
                    while (1) {
                        if (++pos > strlen(buffer))
                        return 0;
                        c = buffer[pos];
                        if ((c >= '0') && (c <= '9')) {
                            number += c;
                            break;
                        }
                        else if (c == ' ' || c == '\t') {
                            qDebug() << "abc: " << number;
                            file_eof = 1;
                            return 1;
                        }
                        else if (c == '\n') {
                            ++line_no;
                            continue;
                        }
                        else if (c == EOF) {
                            file_eof = 1;
                            qDebug() << "abc- " << number;
                            return 1;
                        }
                    }
                }
                else if (c == EOF) {
                    file_eof = 1;
                    return 0;
                }
                else if (c == '=') {
                    qDebug() << "==22===";
                    while (1) {
                        if (++pos >= strlen(buffer))
                        return 0;
                        c = buffer[pos];
                        if ((c >= '0') && (c <= '9')) {
                            qDebug() << c;
                            while (1) {
                                if (++pos >= strlen(buffer))
                                return 1;
                                c = buffer[pos];
                                if ((c >= '0') && (c <= '9')) {
                                    number += c;
                                    qDebug() << c;
                                }
                                if (c == EOF) {
                                    file_eof = 1;
                                    qDebug() << "abc- " << number;
                                    return 1;
                                }
                                else if ((c >= '0') && (c <= '9')) {
                                    number +c;
                                    continue;
                                }
                            }
                            number += c;
                            if (++pos >= strlen(buffer)) {
                                c = buffer[pos];
                                if (c == EOF) {
                                    file_eof = 1;
                                    return 1;
                                }
                            }
                            continue;
                        }
                        else if (c == ' ' || c == '\t') {
                            qDebug() << "abc: " << number;
                            continue;
                        }
                        else if (c == '\n') {
                            ++line_no;
                            continue;
                        }
                        if (c == EOF) {
                            file_eof = 1;
                            qDebug() << "abc- " << number;
                            return 0;
                        }
                    }
                }
            }
        }
        else if (c == EOF) {
            file_eof = 1;
            return 0;
        }
        else {
            return 0;
        }
    }
    return 1;
}

void handle_ident(int cmd, QString ident, QVariant val)
{
    static int counter = 0;
    QString str;

    prev_node.command  = cmd;
    prev_node.name     = ident;

    // PRINT
    if (!(strcmp(  ident.toLower().toLatin1().data(),
        QString("print").toLower().toLatin1().data()))) {
        str = QString("cmd@print@%1@%2")
            .arg(++counter)
            .arg(val.toString());
        prev_node.value    = str;
        ptr_node.insert(str,prev_node);
    }

    // VAR = <expr>
    else if (cmd == cmd_assign) {
        str = QString("cmd@assign@%1@%2@%3")
            .arg(ident)
            .arg(counter)
            .arg(val.toString());
        prev_node.value    = str;
        ptr_node.insert(str,prev_node);
    }

    // VAR = NEW <ident> ( )
    else if (cmd == cmd_assign_new) {
        str = QString("cmd@new@%1")
            .arg(ident);
        prev_node.value    = str;
        ptr_node.insert(str,prev_node);
    }
}

// --------------------------
// execute collected data ...
// --------------------------
bool evaluate(void)
{
    bool found = false;
    QString str;
    QMapIterator<QString, MyNode> iter(ptr_node);
    while (iter.hasNext())
    {   iter.next();
        str = iter.value().value.toString();
        QRegExp rex("cmd@(\\w+)@(\\w+)@(\\d+)@(\\d+)");
        if (rex.indexIn(str) != -1)  {
            QString sub1 = rex.cap(1);
            QString sub2 = rex.cap(2);
            QString sub3 = rex.cap(3); // counter
            QString sub4 = rex.cap(4);

            if (sub1.toLower() == QString("assign"))
            {   if (iter.value().name == sub2)
                {   QVariant val= sub4;
                    found = true;
                    int m = 0;
                    int i;
                    double d;

                    if (val.convert(QVariant::Int))    {m = 1; i = val.toInt();    }
                    if (val.convert(QVariant::Double)) {m = 2; d = val.toDouble(); }

                    QString str;
                    switch (m) {
                        case 1: str = QString("%1").arg(i); break;
                        case 2: str = QString("%1").arg(d); break;
                    }

                    QMessageBox::information(0,"Print Var",
                    QString("PRINT:  %1").arg(str));

                    break;
                }
            }
        }
    }
    return true;
}

QString oldn;
int op;


bool parseText(char *buffer)
{
    ident .clear();
    number.clear();

    int c;
    if (!(c = if_overchar(buffer))) {
        if (c == 1)
        return true ;
        return false;
    }   return true ;
}

#if 0
qDebug() << "==> " << number;
qDebug() << QString(":::-> %1 = %2 = %3 ++ %4")
        .arg(ident)
        .arg(QChar(c))
        .arg(number)
        .arg(oldn);

handle_ident(cmd_assign,ident,number);
ident .clear();
number.clear();

#endif


bool parseText(QString str)
{
    char buffer[str.size()+1];
    bool r = false;
    try {
        line_no = 1;
        pos = -1;
        file_eof = 0;

        ptr_node.clear();
        ident .clear();
        number.clear();

        strcpy(buffer,str.toLatin1().data());
        std::cout << buffer << "\n";

        while (1) {
            r = parseText((char*)buffer);
            if (!r) {
                if (!file_eof) {
                    QMessageBox::critical(0,"Error",
                    QString("Syntax Error in line: %1").arg(line_no));
                    return false;
                }
            }
            QMessageBox::information(0,"Info","SUCCESS");
            //evaluate();

            if (!file_eof) return true;
            file_eof = 0;
            continue;
        }
    }
    catch (QString &e) {
        QMessageBox::critical(0,"Error",
        QString("Error in line: %1\n%2")
        .arg(line_no)
        .arg(e));
    }
    catch (int &e) {
        if (e > 0) {
            if (e == 2)
            QMessageBox::critical(0,"Error",
            QString("Error in line: %1").arg(line_no));
            r = false;
        }
    }

    return r;
}
