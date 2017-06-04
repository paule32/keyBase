#include <stdio.h>

#include <iostream>
#include <QString>
#include <QVariant>
#include <QMap>
#include <QMessageBox>

int line_no = 1;

struct MyNode {
    QVariant value;
};
QMap<QString, MyNode> app_node;

const int TOK_PRINT = 1;

bool handle_ident(QString ident, QVariant val)
{
    MyNode ptr_node;
    int m = 0;
    int i;
    double d;

    if (val.convert(QVariant::Int))    {m = 1; i = val.toInt();    }
    if (val.convert(QVariant::Double)) {m = 2; d = val.toDouble(); }

    switch (m) {
        case 1: ptr_node.value = i; break;
        case 2: ptr_node.value = d; break;
    }

    app_node.insert(ident,ptr_node);
    return true;
}

bool parseText(char *buffer)
{
    char c;
    int pos = -1;

    QString number, ident;
    number.clear();
    ident .clear();

    while (1) {
        if (++pos > strlen(buffer))
        break;
        c = buffer[pos];
        if (((c >= 'a') && (c <= 'z'))
        ||  ((c >= 'A') && (c <= 'Z'))
        ||   (c == '_')) { c11:
            ident += c;
            while (1) {
                if (++pos >= strlen(buffer))
                goto ende2;
                c = buffer[pos];
                if (((c >= 'a') && (c <= 'z'))
                ||  ((c >= 'A') && (c <= 'Z'))
                ||  ((c >= '0') && (c <= '9'))
                ||   (c == '_')) {
                    ident += c;
                    continue;
                }
                else if (c == '/') {
                    while (1) {
                        if (++pos >= strlen(buffer))
                        return false;
                        c = buffer[pos];
                        if (c == '/') {
                            while (1) {
                                if (++pos >= strlen(buffer))
                                break;
                                c = buffer[pos];
                                if ((c == '\n')) {
                                    ++line_no;
                                    break;
                                }
                            }
                            break;
                        }
                        else if (((c >= 'a') && (c <= 'z'))
                             ||  ((c >= 'A') && (c <= 'Z'))
                             ||  ((c >= '0') && (c <= '9'))
                             ||   (c == '_')) {
                            --pos;
                            goto ende2;
                        }
                        else if (c == ' ' || c == '\t') {
                            goto ende2;
                        }
                        else if (c == '\n') {
                            ++line_no;
                            goto ende2;
                        }
                        else if (c == EOF) {
                            return false;
                        }
                    }
                    goto ende2;
                }
                else if (c == ' ' || c == '\t') {
                    if (ident == QString("print"))
                    goto ende2;
                    continue;
                }
                else if (c == '\n') {
                    ++line_no;
                    goto ende2;
                }
                else if (c == EOF) { goto ende2; }
                else if (c == '=') {
                    while (1) {
                        if (++pos >= strlen(buffer))
                        return false;
                        c = buffer[pos];
                             if ((c >= '0') && (c <= '9')) { goto  n4; }
                        else if (c == ' ' || c == '\t') {
                            continue;
                        }
                        else if (c == '\n') {
                            ++line_no;
                            continue;
                        }
                        else if (c == EOF) {
                            return false;
                        }
                    }
                }
                else {
                    break;
                }   break;
            }
            ende2:
            //QMessageBox::information(0,"Infor",ident);

            // ----------------------
            // print expr ...
            // ----------------------
            if (ident.toLower() == QString("print")) {
                ident.clear();
                while (1) {
                    if (++pos >= strlen(buffer))
                    return false;
                    c = buffer[pos];
                    if      (((c >= 'a') && (c <= 'z'))
                         ||  ((c >= 'A') && (c <= 'Z'))
                         ||  ((c >= '0') && (c <= '9'))
                         ||   (c == '_')) {
                        ident += c;
                        while (1) {
                            if (++pos >= strlen(buffer))
                            goto ende3;
                            c = buffer[pos];
                            if (((c >= 'a') && (c <= 'z'))
                                 ||  ((c >= 'A') && (c <= 'Z'))
                                 ||  ((c >= '0') && (c <= '9'))
                                 ||   (c == '_')) {
                                ident += c;
                                continue;
                            }
                            else if (c == ' ' || c == '\t') {
                                goto ende3;
                            }
                            else if (c == '\n') {
                                ++line_no;
                                goto ende3;
                            }
                            else if (c == EOF) {
                                goto ende3;
                            }
                        }
                    }
                }
                ende3:
                QMapIterator<QString, MyNode> iter(app_node);
                bool found = false;
                while (iter.hasNext()) {
                    iter.next();
                    if (iter.key() == ident) {
                        QVariant val = iter.value().value;
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
                        QString("PRINT: %1").arg(str));

                        break;
                    }
                }
                // todo: v = 0;
                if (found == false)
                throw QString("Variable '%1' nicht definiert.").arg(ident);
            }
            ident.clear();
            continue;
        }
        else if (c == '/') {
        //n5:
            if (++pos >= strlen(buffer))
            return false;
            c = buffer[pos];
            if (c == '/') {
                while (1) {
                    if (++pos >= strlen(buffer))
                    break;
                    c = buffer[pos];
                    if ((c == '\n')) {
                        ++line_no;
                        break;
                    }
                    else if (c == EOF) {
                        return true;
                    }
                }
            }
            else if (c == ' ' || c == '\t') {
            n10:
                while (1) {
                    if (++pos >= strlen(buffer)) return false;
                    c = buffer[pos];
                    if ((c == '\n'))  {  ++line_no;      continue; }
                    else if (c == ' ' || c == '\t')    { continue; }

                    else if (((c >= 'a') && (c <= 'z'))
                         ||  ((c >= 'A') && (c <= 'Z'))
                         ||  ((c >= '0') && (c <= '9'))
                         ||   (c == '_')) { goto c11; }
                    else if ((c >= '0') && (c <= '9')) { goto  n4; }
                    else if (c == EOF) {
                        return false;
                    }
                }
            }
            else if (((c >= 'a') && (c <= 'z'))
                 ||  ((c >= 'A') && (c <= 'Z'))
                 ||  ((c >= '0') && (c <= '9'))
                 ||   (c == '_')) { goto c11; }
            else if ((c >= '0') && (c <=  '9')) { goto n3; }
            else if (c == '\n') {
                ++line_no;
                goto n10;
            }
            else {
                return false;
            }
        }
        else if ((c >= '0') && (c <= '9')) { n4:
            while (1) {
            n3:
                number += c;
                if (++pos >= strlen(buffer)) goto ende1;
                c = buffer[pos];

                if ((c >= '0') && (c <= '9')) { continue; }
                else if (c == '.' )           { continue; }

                else if (c == '\n') { ++line_no; goto ende1; }
                else if (c == '/' ) { goto ende1; }
                else if (c == EOF ) {              break; }

                else if (c == ' ' || c == '\t') { goto ende1; }
                else {
                     --pos;
                     break;
                }
            }
            ende1:
            /*QMessageBox::information(0,"Info",
            QString("%1 ==> %2")
            .arg(ident)
            .arg(number));*/

            handle_ident(ident,  number);
            ident .clear();
            number.clear();

            if (c == EOF)
            return true;
            continue;
        }
        else if (c == EOF)  { return true; }
        else if (c == ' ' || c == '\t') { continue; }
        else if (c == '\n') { ++line_no;  continue; }
        else {
            break;
        }
    }
    return true;
}

bool parseText(QString str)
{
    char buffer[str.size()+1];
    bool r = false;
    line_no = 1;
    try {
        strcpy(buffer,str.toLatin1().data());
        std::cout << buffer << "\n";
        r = parseText((char*)buffer);

        if (!r)
        QMessageBox::critical(0,"Error",
        QString("Syntax Error in line: %1").arg(line_no));
        else
        QMessageBox::information(0,"Info","SUCCESS");
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
