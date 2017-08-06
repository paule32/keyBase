#include <QString>
#include <QStringList>
#include <QMessageBox>
#include <QRegExp>
#include <QDebug>

#include "qstringerror.h"

namespace  kallup {
extern int line_no;
}

int linerow = -1;
int linecol =  0;
int pos;

int bracket_counter = 0;

float handle_bracket(QStringList list)
{
    for (int l = 0; l < list.count(); ++l) {
        QString str = list[l];
        for (int i = 0; i < str.length(); i++) {
            if (str[i].toLatin1() == QChar(' '))
            continue;

            if (str[i].toLatin1() == QChar('\n')
            ||  str[i].toLatin1() == QChar(';')) {
                linerow += 1;
                linecol  = 0;
                break;
            }

            if (str[i].toLatin1() == QChar('(')) {
                ++bracket_counter;
                continue;
            }

            if (str[i].toLatin1() == QChar(')')) {
                --bracket_counter;
                qDebug() << "counter: " << bracket_counter;
                if (bracket_counter == 0) {
                    qDebug() << "empty list:01";
                    return 2.31;
                }

                if (bracket_counter < 0)
                throw QStringError(QString("open bracket missing."));
            }
        }
    }

    // missing closed bracket
    throw QStringError(QString("closed bracket missing."));
    return 0.00f;
}

bool parser_lisp(QString src)
{
    QStringList list;
    list = src.split(QChar('\n'));

    qDebug() << list;

    linerow = -1;
    linecol =  0;

    bracket_counter = 0;

    while (1) {
        ++linerow;
        ++linecol;
        if (linerow >= list.count())
        break;

        // blank line
        if (list.at(linerow).trimmed().length() < 1) {
            linecol = 0;
            continue;
        }

        if (list.at(linerow).simplified().at(0) == QChar(' ')) {
            linecol = 0;
            continue;
        }

        if (list.at(linerow).simplified().at(0) == QChar('\n')) {
            linecol = 0;
            continue;
        }

        // lisp comment over line
        linecol = list.at(linerow).indexOf(QChar(';'));
        if (linecol > 0) {
            if (list.at(linerow).at(linecol) == QChar(';'))
            linecol = 0;
            continue;
        }

        pos = list.at(linerow).indexOf('(');
        if (pos >= 0) {
            float result = handle_bracket(list);
            qDebug() << "result: " << result;
        }
    }

    qDebug() << "lstlen: " << list.count();
    qDebug() << "lines handled: " << linerow;
    return true;
}

bool parse_lisp(QString src)
{
    try {
        return parser_lisp(src);
        //Parser<Lisp> p;
        //return p.start(src);
    }
    catch (QStringError e) {
        QMessageBox::critical(0,"Error",
        QString("Error in line: %1\n%2")
        .arg(linerow+1)
        .arg(e.what));
    }
    catch (...) {
        QMessageBox::information(0,"Error",
        "unknow error occur.");
    }
    return false;
}
