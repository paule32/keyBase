#include "mydesignergraphicsview.h"
#include "mydesignercomponents.h"
#include "mydesignerscene.h"
#include "mydesigneritem.h"

#include <QDebug>

MyDesignerGraphicsView::MyDesignerGraphicsView(QWidget * parent)
    : QGraphicsView(parent)
{
    setObjectName("dBaseDesigner");
    setAcceptDrops(true);

    scene = new MyDesignerScene(this);
    scene->setSceneRect(0,0,800,600);
    scene->setObjectName("dBaseDesignerScene");

    this->setScene(scene);
    setDragMode(QGraphicsView::RubberBandDrag);

    DesignerPushButtonItem *btn = new
    DesignerPushButtonItem(QString("ok push"),QRect(100,100,100,40), scene);

    qDebug() << "graph init";
}

void MyDesignerGraphicsView::keyPressEvent(QKeyEvent *event)
{
    //if (event->key() == Qt::Key_F1)
}

void MyDesignerGraphicsView::dropEvent(QDropEvent * event)
{
    event->accept();

    qDebug() << "duspsr";

    QObject * obj = event->source();
    MyDesignerComponents * ptr = dynamic_cast<
    MyDesignerComponents * >(obj);

    if (!ptr) {
        qDebug() << ptr->currentItem()->text();
        if (ptr->currentItem()->text() == "Push Button") {
            DesignerPushButtonItem * item = new
            DesignerPushButtonItem("PushMe",QRect(
                event->pos().x() - 100,
                event->pos().y() , 100, 100),
                scene);
            return;
        }
    }
}

void MyDesignerGraphicsView::dropMoveEvent(QDragMoveEvent * event) { event->accept(); }
