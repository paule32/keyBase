#ifndef MYDESIGNERGRAPHICSVIEW_H
#define MYDESIGNERGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QDragMoveEvent>

#include "mydesignerscene.h"

class MyDesignerGraphicsView: public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyDesignerGraphicsView(QWidget *parent = 0);
    MyDesignerScene * getScene() const { return scene; }
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void dropMoveEvent(QDragMoveEvent *event);
private:
    MyDesignerScene * scene;
};

#endif // MYDESIGNERGRAPHICSVIEW_H
