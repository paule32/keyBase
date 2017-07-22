#ifndef FORM_H
#define FORM_H

#include <QWidget>

#include "ui_haupt.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

    Ui::Form *ui;
private slots:
    void on_listWidget_3_doubleClicked(const QModelIndex &index);
};

#endif // FORM_H
