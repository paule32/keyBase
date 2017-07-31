#include <QPoint>
#include <QVector>
#include <QPolygon>
#include <QPainterPath>

#include <QDebug>

#include "my2dworld.h"
#include "mainwindow.h"

namespace iso2Dview
{
    int level1[3][3] = {
        { 10, 11, 13 },
        { 20, 21, 23 },
        { 30, 31, 33 }
    };
}
using namespace iso2Dview;

my2dworld::my2dworld() { }
my2dworld::my2dworld(QWidget *parent)
    : QWidget(parent)
{
    this->setMouseTracking(true);

    tile_width  = 64;
    tile_height = 64;

    level_xt = level_yt = 5;

    path_poly.clear();
    path_poly.resize(0);

    poly = 0;
}

void my2dworld::mouseMoveEvent(QMouseEvent *event)
{
    tile_no = getTile(event->pos());
    repaint();
}

int my2dworld::getTile(QPoint pt)
{
    int mat = path_poly.count();
    int cnt = 0;
    while (cnt++ != level_yt)
    {   for (int c = 1; c < mat+1; ++c) {
            if (path_poly.at(c-1).contains(QPointF(QPoint(pt))))
            return c;
        }
    }
    return 0;
}

QPolygon my2dworld::setupPoly(int x, int y) {
    QPoint tilept;
    QPolygon tpol;

    tilept.setX(x);
    tilept.setY(y);

    tpol << QPoint(tilept.x() ,  tilept.y()            )
         << QPoint(tilept.x() + (tile_width /2),
                   tilept.y() + (tile_height/2))
         << QPoint(tilept.x() ,  tilept.y()+tile_height)
         << QPoint(tilept.x() - (tile_height/2),
                   tilept.y() + (tile_height/2))
         << QPoint(tilept.x() ,  tilept.y());
    return tpol;
}

void my2dworld::paintEvent(QPaintEvent *) {
    QPainter p(this);
    QPainterPath pp;
    QPolygon pg;
    QString buffer =
    QString("tile: %1 ").arg(tile_no);

    static int flag = 0;

    for (ymap = 1 ; ymap < level_yt+1; ymap++) {
    for (xmap = 1 ; xmap < level_xt+1; xmap++) {
        pg = setupPoly(tile_width *(xmap-1),
                       tile_height*(ymap-1));
        if (flag == 0) {
            pp.addPolygon(pg);
            path_poly.append(pp);
        }

        p.setPen(QColor(Qt::black));
        p.drawPolygon(pg);
        p.drawText(50,50,buffer);
    }   }

    flag = 1;
}

void my2dworld::drawBoard() { }
