#include "mydesignergraphicsview.h"
#include "mydesignerscene.h"

MyDesignerGraphicsView::MyDesignerGraphicsView(QWidget * parent)
    : QGraphicsView(parent)
{
    setObjectName("dBaseDesigner");
    setAutoDrops(true);

    scene = new MyDesignerScene(this);
    scene->setSceneRect(0,0,800,600);
    scene->setObjectName("dBaseDesignerScene");

    setScene(scene);
    setDragMode(QGraphicsView::RubberBandDrag);


}

void MyDesignerGraphicsView::keyPressEvent(QKeyEvent *event)
{
    //if (event->key() == Qt::Key_F1)
}

void MyDesignerGraphicsView::dropEvent(QDropEvent * event)
{
    event->accept();

    QObject * obj = event->source();
    components_draglist * ptr = dynamic_cast<
    components_draglist * >(obj);

    if (!ptr) {

    }
}

void MyDesignerGraphicsView::dropMoveEvent(QDragMoveEvent * event) { event->accept(); }

void
