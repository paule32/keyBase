#ifndef MYDESIGNERCOMPONENTS_H
#define MYDESIGNERCOMPONENTS_H

#include <QWidget>
#include <QListWidget>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMouseEvent>

class MyDesignerComponents : public QListWidget
{
    Q_OBJECT
public:
    explicit MyDesignerComponents(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // MYDESIGNERCOMPONENTS_H
