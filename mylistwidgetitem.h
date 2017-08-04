#ifndef MYLISTWIDGETITEM_H
#define MYLISTWIDGETITEM_H

#include <QString>
#include <QListWidget>
#include <QListWidgetItem>

class MyListWidgetItem: public QListWidgetItem
{
public:
    explicit MyListWidgetItem(QListWidget * parent, QString name, QString icon_res, int mode);
};

#endif // MYLISTWIDGETITEM_H
