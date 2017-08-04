#include "mydesignerscene.h"
#include <QPen>
#include <QPainter>

MyDesignerScene::MyDesignerScene(QObject *parent)
    : QGraphicsScene(parent)
    , gridSize(20)
{
    Q_ASSERT(gridSize > 0);
}

void MyDesignerScene::drawBackground(QPainter *painter, QRectF &rect)
{
    QPen pen;
    painter->setPen(pen);

    qreal left = int(rect.left()) - (int(rect.left()) % gridSize);
    qreal top  = int(rect.top ()) - (int(rect.top ()) % gridSize);

    QVector<QPointF> points;

    for (qreal x = left; x < rect.right (); x += gridSize) {
    for (qreal y = top ; y < rect.bottom(); y += gridSize) {
        points.append(QPointF(x,y));
    }   }

    painter->drawPoints(points.data(), points.size());
}
