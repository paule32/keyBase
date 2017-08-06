#ifndef MYDESIGNERGRAPHICSVIEW_H
#define MYDESIGNERGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QDragMoveEvent>
#include <QDragEnterEvent>

#include "mydesignerscene.h"

class MyDesignerGraphicsView: public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyDesignerGraphicsView(QWidget *parent = 0);
    MyDesignerScene * getScene() const { return scene; }
protected:
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
private:
    MyDesignerScene * scene;
};

#endif // MYDESIGNERGRAPHICSVIEW_H
