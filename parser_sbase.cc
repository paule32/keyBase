#include <stdio.h>

#include <iostream>
#include <QString>
#include <QMessageBox>

int line_no = 1;

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
            QMessageBox::information(0,"Infor",ident);
            ident.clear();
            continue;
        }
        else if (c == '/') {
        n5:
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
            QMessageBox::information(0,"Info",
            QString("==> %1").arg(number));

            if (c == EOF)
            return true;

            number.clear();
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
