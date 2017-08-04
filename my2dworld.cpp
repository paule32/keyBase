#include <QPoint>
#include <QVector>
#include <QCursor>
#include <QPicture>
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

    level_xt = level_yt = 4;

    path_poly.clear();
    path_poly.resize(0);

    poly = 0;
}

void my2dworld::leaveEvent(QEvent *) { qApp->setOverrideCursor(QCursor(Qt::ArrowCursor)); }
void my2dworld::enterEvent(QEvent *)
{
    QPixmap pixmap("./img/mouseptr.png");
    if (pixmap.isNull()) qDebug() << "pixmap error";
    QCursor mouse_pointer(pixmap,1,1);
    qApp->setOverrideCursor(mouse_pointer);
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
    }   }
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
    QPainterPath pp1,pp2;
    QPolygon pg1,pg2;
    QString buffer;

    static int flag = 0;

    for (ymap = 1 ; ymap < level_yt+1; ymap++) {
    for (xmap = 1 ; xmap < level_xt+2; xmap++) {
        pg1= setupPoly((tile_width  )*(xmap-1)+32,
                       (tile_height )*(ymap-1));
        pg2= setupPoly((tile_width  )*xmap-(tile_width/2)+32,
                       (tile_height )*ymap-(tile_height+32));
        pp1.addPolygon(pg1);
        pp2.addPolygon(pg2);

        if (flag == 0) {
            path_poly.append(pp1);
            path_poly.append(pp2);
        }

        p.fillPath(pp1,QBrush(QColor(Qt::black)));
        p.fillPath(pp2,QBrush(QColor(Qt::white)));

        p.setPen(QColor(Qt::black)); p.drawPolygon(pg1);
        p.setPen(QColor(Qt::red));   p.drawPolygon(pg2);

        if ((tile_no >= 1) && (tile_no <= 50)) {
            QPixmap pixmap("./img/road1.png");
            p.fillPath(pp1,QBrush(QPixmap(pixmap)));
            p.drawText(200,270,"gtaass");
        }
    }   }

    buffer = QString("tile: %1 ").arg(tile_no);
    p.setPen(QColor(Qt::black));
    p.drawText(50,300,buffer);

    flag = 1;
}
