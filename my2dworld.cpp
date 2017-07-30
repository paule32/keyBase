#include <QVector>
#include <QPolygon>

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

    pixies.clear();
    poly = 0;
}

void my2dworld::mouseMoveEvent(QMouseEvent *event)
{
    tile_no = getTile(event->pos());
    repaint();
}

int my2dworld::getTile(QPoint pt)
{
    QPolygon *po = pixies.data();
    for (int i = 0; i < pixies.size(); ++i) {
    if (po[i].containsPoint(pt,Qt::OddEvenFill))
        return i+1;
    }   return 0;
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
    QPainter p(this); int tmp;
    QPolygon pg;
    QString buffer =
    QString("tile: %1 ").arg(tile_no);

    static int flag = 0;
    tmp = 0;

    for (ymap = 1 ; ymap < level_yt+1; ymap++) {
    for (xmap = 1 ; xmap < level_xt+1; xmap++) {
        if (flag == 0) {
            pg = setupPoly((tile_width *xmap) - tile_width,
                           (tile_height*ymap) - tile_height);
            pixies.append(pg);
        }

        p.setPen(QColor(Qt::black));
        p.drawPolygon(pixies.at(tmp++));
        p.drawText(50,50,buffer);
    }   }

    flag = 1;
}

void my2dworld::drawBoard() { }
