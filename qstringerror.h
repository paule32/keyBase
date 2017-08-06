#ifndef QSTRINGERROR_H
#define QSTRINGERROR_H

#include <QString>

// ----------------------------------------
// exception classes for error handling ...
// ----------------------------------------
class QStringError {
public:
    QStringError(QString str) { what = str; }
    QStringError()            { what = QString("common mistake"); }
    QString what;
};

#endif // QSTRINGERROR_H
